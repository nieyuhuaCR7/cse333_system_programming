#include "ro_file.h"

#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>


/*** INTERNAL DATA TYPES AND CONSTANTS **************************************/

static const int RO_FILE_BUF_LEN = 512;  // do not modify

struct ro_file_st {
  int fd;         // The file descriptor we are currently managing.

  char* buf;      // Pointer to our internal buffer for this file.

  off_t buf_pos;  // The position in the file that the beginning of our
                  // internal buffer currently corresponds to.

  int buf_index;  // The index in our internal buffer that corresponds to the
                  // user's current position in the file.

  int buf_end;    // How many bytes currently in our internal buffer are
                  // actually from the file.
                  // To understand why this is important to track, consider
                  // the case when the file length is < RO_FILE_BUF_LEN.
};


/*** STATIC HELPER FUNCTION DECLARATIONS ************************************/

// Copy up to 'amount' bytes from the RO_FILE's internal buffer to 'out'.
// Returns the number of bytes copied.
static size_t flush_buffer(RO_FILE* file, char* out, int amount);

// Fill in the RO_FILE's internal buffer with as many bytes as can be read
// from the file.
// Returns the number of bytes copied into the buffer, or -1 on any error.
static ssize_t fill_buffer(RO_FILE* file);


/*** FUNCTION DEFINITIONS ***************************************************/

// TODO: Write this function
RO_FILE* ro_open(char* filename) {
  // 1. Allocate a new RO_FILE
  RO_FILE *file = (RO_FILE*)malloc(sizeof(RO_FILE));
  // check if a new RO_FILE is correctly allocated, return NULL if not
  if (file == NULL) {
    return NULL;
  }

  // 2. Get the file descriptor for the file
  file->fd = open(filename, O_RDONLY); // use the POSIX function open(), read-only mode
  // check if the open function returns correctly
  if (file->fd < 0) {
    // free the struct
    free(file);
    return NULL;
  }

  // 3. Allocate the internal buffer
  file->buf = (char*)malloc(RO_FILE_BUF_LEN*sizeof(char));
  if (file->buf == NULL) {
    close(file->fd);
    free(file);
    return NULL;
  }

  // 4. Initialize the other fields (no reading done yet)
  file->buf_pos = 0;
  file->buf_index = 0;
  file->buf_end = 0;

  return file;
}

ssize_t ro_read(char* ptr, size_t len, RO_FILE* file) {
  // 1. If we have bytes in our internal buffer, flush as many as we can to
  //    'ptr'.
  size_t num_copied_out = flush_buffer(file, ptr, len);

  while (num_copied_out != len) {
    // 2. If we haven't provided the bytes requested, repopulate our buffer
    //    with bytes from the file.
    ssize_t num_filled = fill_buffer(file);
    if (num_filled == 0) {
      // reached EOF; no more bytes to copy
      break;
    } else if (num_filled < 0) {
      // pass error back to client
      return num_filled;
    }

    // 3. Copy filled bytes into 'ptr'.
    num_copied_out += flush_buffer(file, ptr+num_copied_out,
                                   len-num_copied_out);

    // 4. Repeat steps 2-3 until request is fulfilled.
  }

  return num_copied_out;
}

off_t ro_tell(RO_FILE* file) {
  if (file == NULL) {
    return -1;
  }
  return file->buf_pos + file->buf_index;
}

// TODO: Write this function
int ro_seek(RO_FILE* file, off_t offset, int whence) {
  // 1. Check validity of arguments, where applicable.
  if (file == NULL||(whence != SEEK_SET && whence != SEEK_CUR && whence != SEEK_END)) {
    errno = EINVAL;
    return 1;
  }

  // 2. Seek to specified offset from specified whence using lseek.
  //    No need to check if new position is already in our buffer.
  off_t new_pos = lseek(file->fd, offset, whence);
  if (new_pos < 0) {
    errno = EINVAL;
    return 1;
  }

  // 3. Update our buffer indicators
  file->buf_pos = new_pos;
  file->buf_index = 0;
  file->buf_end = 0;

  return 0;
}

// TODO: Write this function
int ro_close(RO_FILE* file) {
  // Clean up all RO_FILE resources, returns non-zero on error
  if (file == NULL) {
    return 1;
  }

  int ret = close(file->fd);
  free(file->buf);
  free(file);
  return ret;
}


/*** STATIC HELPER FUNCTION DEFINITIONS *************************************/

// TODO: Write this function
size_t flush_buffer(RO_FILE* file, char* out, int amount) {
  // 1. Copy/flush bytes to 'out' starting from the buffer index. The amount
  //    flushed should be the min of 'amount' and the remaining unflushed bytes
  //    in the buffer.
  int num_to_flush;
  int remainder = file->buf_end - file->buf_index; // 内部缓冲区中剩余未刷新的字节数
  if (remainder <= amount) {
    num_to_flush = amount;
  } else {
    num_to_flush = remainder;
  }

  memcpy(out, file->buf + file->buf_index, num_to_flush);
  
  // 2. Advance buffer index by the number of bytes flushed.
  file->buf_index += num_to_flush;

  // 3. Return the number of bytes flushed.
  return num_to_flush;
}

// TODO: Write this function
ssize_t fill_buffer(RO_FILE* file) {
  // NOTES:
  // - For maximum buffering benefit, we are "resetting" the buffer and then
  //   filling it with as much file data as possible, starting from the current
  //   file position -- how does this change the buffer indicators?
  // - For simplicity, you should ignore any unflushed bytes that started in
  //   the buffer (i.e., it's okay to re-read them from the file).
  // - You will need to implement a POSIX read loop with all appropriate
  //   return value checking.
  file->buf_index = 0;
  file->buf_end = 0;
  ssize_t total_bytes_read = 0;
  ssize_t bytes_read;

  do {
    bytes_read = read(file->fd, file->buf + total_bytes_read, RO_FILE_BUF_LEN - total_bytes_read);
    if (bytes_read < 0) {
      if (errno = EINTR) {
        continue;
      } else {
        return -1;
      }
    } else if (bytes_read == 0) {
      break;
    }
    total_bytes_read += bytes_read;

  } while(total_bytes_read < RO_FILE_BUF_LEN);

  file->buf_end = total_bytes_read;
  file->buf_pos += total_bytes_read;

  return total_bytes_read;
}
