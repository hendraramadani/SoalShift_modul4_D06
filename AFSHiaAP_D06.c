#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>

static const char *dirpath = "/home/dani/shift4";

void encrypt(const char *name, int indent)
{
    char tes[94] = "qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0";
    //printf("%ld",strlen(tes));
    DIR *dir;
    char buffer[1000],buffer2[1000],buffer3[1000],hasil[1000],ch,ce;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) {
            memset(hasil,0,1000);
            memset(buffer,0,1000);
            memset(buffer2,0,1000);
            memset(buffer3,0,1000);
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            strcpy(buffer, entry->d_name);
            //printf("%s\n", buffer);

            strcat(buffer2,name);
            strcat(buffer2,"/");
            

            for(int i=0;i<strlen(buffer);i++){
			ch = buffer[i];
                if(ch == '/'){
                    ce = '/';

                    hasil[i] = ce;
                }
                else{
                    for(int j=0;j<strlen(tes);j++){
                        if(ch == tes[j]){
                            int a = (j+17)%94;
                            ce = tes[a];
                        }
                    hasil[i] = ce;
                        }
                    }
            }
            //strcpy(hasil,"");
            strcat(buffer2,hasil);
            rename(path,buffer2);
            strcpy(path,buffer2);
            //printf("%*s[%s]\n", indent, "", entry->d_name);
            // memset(hasil,0,1000);
            // memset(buffer,0,1000);
            // memset(buffer2,0,1000);
            // memset(buffer3,0,1000);
            encrypt(path, indent + 2);
        } else {
            strcpy(buffer, entry->d_name);
            //printf("%s\n", buffer);

            strcat(buffer2,name);
            strcat(buffer2,"/");
            strcat(buffer3,buffer2);
            strcat(buffer2,entry->d_name);

            
            

            for(int i=0;i<strlen(buffer);i++){
			ch = buffer[i];
                if(ch == '/'){
                    ce = '/';

                    hasil[i] = ce;
                }
                else{
                    for(int j=0;j<strlen(tes);j++){
                        if(ch == tes[j]){
                            int a = (j+17)%94;
                            ce = tes[a];
                        }
                    hasil[i] = ce;
                        }
                    }
            }
            strcat(buffer3,hasil);
           // printf("%s\n", buffer2);
           // printf("%s\n", buffer3);


            rename(buffer2,buffer3);

        }
            
    }

    //memset(hasil,0,1000);
    closedir(dir);
}

void decrypt(const char *name, int indent)
{
    char tes[94] = "qE1~ YMUR2\"`hNIdlzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0";
    //printf("%s",tes);
    DIR *dir;
    char buffer[1000],buffer2[1000],buffer3[1000],hasil[1000],ch,ce;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) {
            memset(hasil,0,1000);
            memset(buffer,0,1000);
            memset(buffer2,0,1000);
            memset(buffer3,0,1000);
            
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            strcpy(buffer, entry->d_name);
            //printf("%s\n", buffer);

            strcat(buffer2,name);
            strcat(buffer2,"/");
            

            for(int i=0;i<strlen(buffer);i++){
			ch = buffer[i];
                if(ch == '/'){
                    ce = '/';

                    hasil[i] = ce;
                }
                else{
                    for(int j=0;j<strlen(tes);j++){
                        if(ch == tes[j]){
                            int a = abs((j-17))%94;
                            printf("%d ",a);
                            ce = tes[a];
                        }
                    hasil[i] = ce;
                        }
                    }
            }
            //strcpy(hasil,"");
            strcat(buffer2,hasil);
            rename(path,buffer2);
            strcpy(path,buffer2);
            printf("%s",path);
            //printf("%*s[%s]\n", indent, "", entry->d_name);
            // memset(hasil,0,1000);
            // memset(buffer,0,1000);
            // memset(buffer2,0,1000);
            // memset(buffer3,0,1000);
            decrypt(path, indent + 2);


        } else {
            strcpy(buffer, entry->d_name);
            //printf("sebelum decrypt: %s\n", buffer);

            strcat(buffer2,name);
            strcat(buffer2,"/");
            strcat(buffer3,buffer2);
            strcat(buffer2,entry->d_name);

            
            

            for(int i=0;i<strlen(buffer);i++){
			ch = buffer[i];
                if(ch == '/'){
                    ce = '/';

                    hasil[i] = ce;
                }
                else{
                    for(int j=0;j<strlen(tes);j++){
                        if(ch == tes[j]){
                            int a = abs((j-17))%94;
                            printf("%d ",a);
                            ce = tes[a];
                        }
                    hasil[i] = ce;
                        }
                    }
            }
            strcat(buffer3,hasil);
            //printf("setelah dekrip: %s\n", hasil);
           printf("%s\n", buffer3);


         rename(buffer2,buffer3);

        }

    }

    //memset(hasil,0,1000);
    closedir(dir);
}

static int xmp_getattr(const char *path, struct stat *stbuf)
{
    int res;
	char fpath[1000], fname[1000];

    if(strcmp(path, ".")!=0 && strcmp(path, "..")!=0){
        memset(fname, '\0', sizeof(fname));
        strcpy(fname, path);
        encrypt(fname,0);
        sprintf(fpath, "%s%s", dirpath, fname);
    }
    else{
	    sprintf(fpath,"%s%s",dirpath,path);
    }
	
    res = lstat(fpath, stbuf);

	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
		       off_t offset, struct fuse_file_info *fi)
{
  char fpath[1000];
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else sprintf(fpath, "%s%s",dirpath,path);
	int res = 0;

	DIR *dp;
	struct dirent *de;

	(void) offset;
	(void) fi;

	dp = opendir(fpath);
	if (dp == NULL)
		return -errno;

    decrypt(path,0);

	while ((de = readdir(dp)) != NULL) {
		struct stat st;
		memset(&st, 0, sizeof(st));
        
		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;
		res = (filler(buf, de->d_name, &st, 0));
			if(res!=0) break;
	}

	closedir(dp);
	return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,
		    struct fuse_file_info *fi)
{
  char fpath[1000];
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else sprintf(fpath, "%s%s",dirpath,path);
	int res = 0;
  int fd = 0 ;

	(void) fi;
	fd = open(fpath, O_RDONLY);
	if (fd == -1)
		return -errno;

	res = pread(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	return res;
}

static struct fuse_operations xmp_oper = {
	.getattr	= xmp_getattr,
	.readdir	= xmp_readdir,
	.read		= xmp_read,
};

int main(int argc, char *argv[])
{   
    encrypt(dirpath, 0);
	umask(0);
	return fuse_main(argc, argv, &xmp_oper, NULL);
}