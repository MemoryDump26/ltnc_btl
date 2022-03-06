# ltnc_btl
Bài tập lớn môn LTNC của Lê Trọng Bảo (21020608)

### Project này sử dụng hệ thống make có trên linux.
#### Build và chạy (Linux):
```
make
./game
```
### Để build trên Windows, ngoài setup ban đầu, "có thể(?)" sẽ phải edit source code như sau:
Từ:
```
#include <SDL2/SDL.h>
```
Chuyển thành:
```
#include <SDL.h>
