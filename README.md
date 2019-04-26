# SoalShift_modul4_D06

## Soal 1
### Semua File Terenkripsi.
Enkripsi yang Atta inginkan sangat sederhana, yaitu Caesar cipher. Namun, Kusuma mengatakan enkripsi tersebut sangat mudah dipecahkan. Dia menyarankan untuk character list diekspansi,tidak hanya alfabet, dan diacak. Berikut character list yang dipakai:

  `qE1~ YMUR2"hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\8s;g<{3.u*W-0`

Misalkan ada file bernama “halo” di dalam folder “INI_FOLDER”, dan key yang dipakai adalah 17, maka:
“INI_FOLDER/halo” saat belum di-mount maka akan bernama “n,nsbZ]wio/QBE#”, saat telah di-mount maka akan otomatis terdekripsi kembali menjadi “INI_FOLDER/halo” .

Perhatian: Karakter ‘/’ adalah karakter ilegal dalam penamaan file atau folder dalam *NIX, maka dari itu dapat diabaikan

### Jawab
1. membuat fungsi enkripsi

  ```
  void encrypt(const char *name, int indent)
  {
      char tes[94] = "qE1~ YMUR2\"``hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0";
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

  ```  

- sebelum dimount folder target yang akan dimount akan dienkripsi dan nantinya ketika dimount folder target akan didekripsi

2. Kemudian membuat fungsi dekripsi

  ```
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
  ```
  - namun untuk fungsi deskripnya masih belum berhasil
  
## Soal 2
### Semua file video yang tersimpan secara terpecah-pecah (splitted) harus secara otomatis tergabung (joined) dan diletakkan dalam folder “Videos” Urutan operasi dari kebutuhan ini adalah:

1. Tepat saat sebelum file system di-mount
- Secara otomatis folder “Videos” terbuat di root directory file system
- Misal ada sekumpulan file pecahan video bernama “computer.mkv.000”, “computer.mkv.001”, “computer.mkv.002”, dst. Maka secara otomatis file pecahan tersebut akan di-join menjadi file video “computer.mkv”
- Untuk mempermudah kalian, dipastikan hanya video file saja yang terpecah menjadi beberapa file. File pecahan tersebut dijamin terletak di root folder fuse
- Karena mungkin file video sangat banyak sehingga mungkin saja saat menggabungkan file video, file system akan membutuhkan waktu yang lama untuk sukses ter-mount. Maka pastikan saat akan menggabungkan file pecahan video, file system akan membuat 1 thread/proses(fork) baru yang dikhususkan untuk menggabungkan file video tersebut
Pindahkan seluruh file video yang sudah ter-join ke dalam folder “Videos”
- Jangan tampilkan file pecahan di direktori manapun

2. Tepat saat file system akan di-unmount
- Hapus semua file video yang berada di folder “Videos”, tapi jangan hapus file pecahan yang terdapat di root directory file system
- Hapus folder “Videos” 

## Soal 3
### Sebelum diterapkannya file system ini, Atta pernah diserang oleh hacker LAPTOP_RUSAK yang menanamkan user bernama “chipset” dan “ic_controller” serta group “rusak” yang tidak bisa dihapus. Karena paranoid, Atta menerapkan aturan pada file system ini untuk menghapus “file bahaya” yang memiliki spesifikasi:

- Owner Name 	: ‘chipset’ atau ‘ic_controller’
- Group Name	: ‘rusak’
- Tidak dapat dibaca

Jika ditemukan file dengan spesifikasi tersebut ketika membuka direktori, Atta akan menyimpan nama file, group ID, owner ID, dan waktu terakhir diakses dalam file “filemiris.txt” (format waktu bebas, namun harus memiliki jam menit detik dan tanggal) lalu menghapus “file bahaya” tersebut untuk mencegah serangan lanjutan dari LAPTOP_RUSAK.

## Soal 4
### Pada folder YOUTUBER, setiap membuat folder permission foldernya akan otomatis menjadi 750. Juga ketika membuat file permissionnya akan otomatis menjadi 640 dan ekstensi filenya akan bertambah “.iz1”. File berekstensi “.iz1” tidak bisa diubah permissionnya dan memunculkan error bertuliskan “File ekstensi iz1 tidak boleh diubah permissionnya.”

## Soal 5
### Ketika mengedit suatu file dan melakukan save, maka akan terbuat folder baru bernama Backup kemudian hasil dari save tersebut akan disimpan pada backup dengan nama namafile_[timestamp].ekstensi. Dan ketika file asli dihapus, maka akan dibuat folder bernama RecycleBin, kemudian file yang dihapus beserta semua backup dari file yang dihapus tersebut (jika ada) di zip dengan nama namafile_deleted_[timestamp].zip dan ditaruh ke dalam folder RecycleBin (file asli dan backup terhapus). Dengan format [timestamp] adalah yyyy-MM-dd_HH:mm:ss
