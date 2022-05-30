# EoThon

## Idea:

#### **MR.BA** ####

==========

**LCD2004 hiển thị thông tin**
 - Dòng 1: Chào, hướng dẫn
 - Dòng 2-3: tên lớp, mã lớp, 
 - Dòng 4: mã lớp được nhập vào
 
**Đọc 4 nút bấm**
 - (A)-(B): Nhập mã lớp.
 - (OK): xác nhận đã nhập xong.
 - (SELECT): Dòng 2-3 LCD hiển thị lần lượt các lớp-mã lớp còn lại.

**Robot dò line**

Khi nhập đúng mã lớp, robot dò line từ chạy vào trong đến điểm kiểm dừng chỉ định.
 - sử dụng 2xHallSensor để dò line 
 - 1xHallSensor để detect điểm dừng

Sau khi phát loa hướng dẫn lầu - khóa học, robor dò line từ đi ra cửa đến điểm dừng đã chỉ định

**Phát hiện vật cản**

Dùng 4 siêu âm để đo khoảng cách 4 hướng (Trước-Sau-Trái-Phải)
 - Trong quá trình đi vào trong Siêu âm Trái-Phải sẽ kiểm tra chỗ xe còn trống để hướng dẫn khách. Siêu âm Sau sẽ kiểm tra có vật cản thì dừng lại để tránh va chạm
 - Khi đến điểm dừng **bên trong** đã chỉ định, Siêu âm Phải Phát hiện có vật cản sẽ thông báo phát loa.

 **Phát loa mp3**

Dùng DFPlayer 
 - Hướng dẫn lầu - khóa học
 - Chào-Hướng dẫn khách nhập dữ liệu nút bấm
 - Thông báo sai mã lớp
 - Cảnh báo hết pin
 - Hướng dẫn để xe Trái|Phải
 - Xin đường khi có vật cản Trước|Sau >3s

 ==========
