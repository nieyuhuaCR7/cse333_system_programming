#include <stdio.h>    // for snprintf
#include <stdlib.h>   // for EXIT_SUCCESS, NULL
#include <string.h>   // for strrchr, strcmp, strlen
#include <stdbool.h>  // for bool
#include <dirent.h>   // for DIR*



#define MAX_PATH_LEN 256
#define MAX_BUFF_LEN 1024


/*** HELPER FUNCTION DECLARATIONS ******************************************/

// Returns whether or not a filename ends in ".txt".
bool IsTxtFile(char* filename);

// Concatenate the directory and file names into a full path. The caller is
// responsible for freeing the allocated string. Exits if an error occurs.
char* Concatenate(char* dirname, char* filename);


/*
 * This program:
 * - Accepts a directory name as a command-line argument.
 * - Scans through the directory looking for all files whose names end with
 *   the four characters ".txt".
 * - For every such file found, write the contents of those files to stdout
 *   without adding any additional characters or formatting.
 *   Eventually reading the files with ro_file module.
 */
int main(int argc, char** argv) {
  // TODO: Write this function
  DIR *dir;
  struct dirent *ent;
  char path[MAX_PATH_LEN];
  char buff[MAX_BUFF_LEN];
  FILE *fp;

  // check the parameter number
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
    return EXIT_FAILURE;
  }

  // open the directory
  dir = opendir(argv[1]);

  if (dir != NULL) {
    // go through every file in this directory
    while ((ent = readdir(dir)) != NULL) {
      // printf("%s\n", ent->d_name);
      if (IsTxtFile(ent->d_name)) {
        // printf("%s\n", ent->d_name);

        // set up the file path into the char array "path"
        snprintf(path, MAX_PATH_LEN, "%s/%s",argv[1], ent->d_name);

        // open this file
        fp = fopen(path, "r");

        size_t readlen;

        if (fp != NULL) {
          // while ((n = fread(buff, 1, MAX_BUFF_LEN, fp) > 0)) {
          //   fwrite(buff, 1, n, stdout);
          // }
          while ((readlen = fread(buff, 1, MAX_BUFF_LEN, fp)) > 0) {
            if (ferror(fp)) {
              perror("fread failed");
              fclose(fp);
              return EXIT_FAILURE;
            }
            
            if (fwrite(buff, 1, readlen, stdout) < readlen) {
              perror("fwrite failed");
              fclose(fp);
              return EXIT_FAILURE;
            }
          }

          // close the file
          fclose(fp);
        } else {
          perror("failed to open the file");
          return 1;
        }
      }
    }
    closedir(dir);
  } else {
    perror("failed to open directory");
    return 1;
  }
  return EXIT_SUCCESS;
}


/*** HELPER FUNCTION DEFINITIONS *******************************************/

bool IsTxtFile(char* filename) {
  char* dot = strrchr(filename, '.');
  return dot && !strcmp(dot, ".txt");
}

char* Concatenate(char* dirname, char* filename) {
  bool has_trailing_slash = dirname[strlen(dirname) - 1] == '/';
  // Concatenate directory and file name.
  size_t dlen = strlen(dirname);
  size_t flen = strlen(filename);
  // Malloc space for full path name:
  // dlen + strlen("/") + flen + strlen('\0') = dlen + flen + 2
  int size_to_malloc = has_trailing_slash ? dlen + flen + 1 : dlen + flen + 2;
  char* fullpath = (char*) malloc(sizeof(char) * (size_to_malloc));
  if (fullpath == NULL) {
    fprintf(stderr, "Error on malloc.\n");
    exit(EXIT_FAILURE);
  }
  if (has_trailing_slash) {
    snprintf(fullpath, size_to_malloc, "%s%s", dirname, filename);
  } else {
    snprintf(fullpath, size_to_malloc, "%s/%s", dirname, filename);
  }
  return fullpath;
}
