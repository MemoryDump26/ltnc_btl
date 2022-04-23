# ltnc_btl
Bài tập lớn môn LTNC của Lê Trọng Bảo (21020608)

### Project này sử dụng hệ thống make có trên Linux.
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
```
### Game:
Sử dụng WASD để di chuyển ô vuông.
Space để nhảy.
Kẻ địch sẽ nhắm tới bạn, dùng chuột di chuyển vũ khí để đỡ.
Khi đỡ được 3 lần, có thể sử dụng chuột trái để bắn.
