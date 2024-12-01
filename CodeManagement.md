# Quy trình xử lý dòng lệnh

## Kiểm tra hợp lệ ban đầu (cờ -a)
1. Kiểm tra xem cờ có phải là "-a" và có tối thiểu 5 đối số
2. Xác thực tên thuật toán tồn tại trong bảng ánh xạ thuật toán
3. Lấy thông tin thuật toán (tên và con trỏ hàm)

## Kiểm tra hợp lệ ban đầu cho cờ -c
1. Kiểm tra số lượng đối số tối thiểu (cần ít nhất 5 đối số):
   - cờ (-c)
   - thuật toán thứ nhất
   - thuật toán thứ hai  
   - tệp/kích thước đầu vào
   - [loại thứ tự cho lệnh 5]

2. Xác thực cả hai thuật toán tồn tại
3. Lấy thông tin cho cả hai thuật toán

## Lệnh 1: `[Execution file] -a [Algorithm] [Input filename] [Output parameter(s)]`
1. Kiểm tra argc == 5 và argv[3] không phải là số
2. Xử lý đầu vào:
   - Mở tệp đầu vào được chỉ định bởi argv[3]
   - Đọc dòng đầu tiên để lấy kích thước mảng (n)
   - Đọc dòng thứ hai để lấy các phần tử mảng
   - Phân tích các số được phân tách bằng dấu cách vào original_array[n]

3. Thao tác mảng:
   - Tạo duplicated_array[n]
   - Sao chép original_array sang duplicated_array

4. Sắp xếp:
   - Gọi algorithm.function(duplicated_array, n)
   - Ghi lại thời gian chạy và số lần so sánh

5. Đầu ra:
   - Tạo output.txt
   - Ghi mảng đã sắp xếp vào output.txt

6. Hiển thị kết quả:
   - Hiển thị tên thuật toán, tệp đầu vào, kích thước
   - Hiển thị thời gian chạy nếu -time hoặc -both
   - Hiển thị số lần so sánh nếu -comp hoặc -both

7. Dọn dẹp:
   - Xóa các mảng
   - Đóng tệp

## Lệnh 2: `[Execution file] -a [Algorithm] [Input size] [Input order] [Output parameter(s)]`
1. Kiểm tra argc == 6
2. Xác thực đầu vào:
   - Xác thực data_order tồn tại
   - Chuyển đổi chuỗi kích thước thành số nguyên

3. Tạo mảng:
   - Tạo original_array[size]
   - Tạo dữ liệu sử dụng hàm thứ tự đã chỉ định

4. Quá trình sắp xếp:
   - Tạo duplicated_array
   - Sao chép và sắp xếp mảng
   - Ghi lại các chỉ số

5. Đầu ra tệp:
   - Ghi mảng gốc vào input.txt
   - Ghi mảng đã sắp xếp vào output.txt

6. Hiển thị:
   - Hiển thị thuật toán, kích thước, thứ tự
   - Hiển thị các chỉ số dựa trên tham số

7. Dọn dẹp

## Lệnh 3: `[Execution file] -a [Algorithm] [Input size] [Output parameter(s)]`
1. Kiểm tra argc == 5 và argv[3] là số
2. Thiết lập:
   - Chuyển đổi chuỗi kích thước thành số nguyên
   - Khởi tạo bộ đếm tệp đầu vào

3. Cho mỗi thứ tự dữ liệu:
   - Tạo mảng với thứ tự hiện tại
   - Sao chép và sắp xếp mảng
   - Ghi đầu vào vào input_[1-4].txt
   - Hiển thị kết quả cho thứ tự hiện tại

4. Định dạng hiển thị:
   - Hiển thị tiêu đề một lần
   - Hiển thị kết quả cho mỗi loại thứ tự
   - Bao gồm các dòng phân cách

5. Dọn dẹp sau mỗi lần lặp

## Lệnh 4: `[Execution file] -c [Algorithm 1] [Algorithm 2] [Input filename]`
1. Xác thực cả hai thuật toán tồn tại
2. Xử lý đầu vào:
   - Đọc kích thước tệp và dữ liệu
   - Tạo mảng gốc

3. Thuật toán thứ nhất:
   - Sao chép mảng
   - Sắp xếp và ghi lại chỉ số

4. Thuật toán thứ hai:
   - Sao chép mảng lại
   - Sắp xếp và ghi lại chỉ số

5. Hiển thị:
   - Hiển thị so sánh song song
   - Cả thời gian chạy và số lần so sánh

6. Dọn dẹp

## Lệnh 5: `[Execution file] -c [Algorithm 1] [Algorithm 2] [Input size] [Input order]`
1. Xác thực:
   - Cả hai thuật toán tồn tại
   - Thứ tự dữ liệu hợp lệ
   - Kích thước có thể chuyển đổi thành số nguyên

2. Tạo mảng:
   - Tạo mảng với kích thước đã chỉ định
   - Áp dụng thứ tự đã chỉ định

3. Sắp xếp thuật toán thứ nhất:
   - Sao chép và sắp xếp
   - Ghi lại chỉ số

4. Sắp xếp thuật toán thứ hai:
   - Sao chép và sắp xếp
   - Ghi lại chỉ số

5. Đầu ra:
   - Ghi mảng đầu vào vào tệp
   - Hiển thị kết quả so sánh

6. Dọn dẹp

## Xử lý lỗi xuyên suốt
- Lỗi mở tệp
- Đối số không hợp lệ
- Cấp phát bộ nhớ
- Tên thuật toán không hợp lệ
- Thứ tự dữ liệu không hợp lệ
- Số lượng đối số không khớp