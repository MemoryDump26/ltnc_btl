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
Sử dụng WASD để di chuyển nhân vật, Space để nhảy.

Kẻ địch sẽ nhắm tới bạn, dùng chuột di chuyển vũ khí để đỡ, kẻ địch bị đỡ sẽ mất một lúc để có thể chạm lại vào người chơi.

Khi đỡ được 3 lần, có thể sử dụng chuột trái để bắn, tiêu diệt kẻ địch.

Nhân vật có 100 HP, mỗi lần bị đánh -20 HP.

Sau khi bị đánh sẽ có 30 "iframe" (khoảng nửa giây).

0 HP thì thua (duh).

Chơi càng lâu thì kẻ địch sẽ sinh ra càng nhanh.

Nếu nghe nhạc nhiều quá đau đầu :> thì có thể tắt bằng phím P, bật lại bằng phím R.
