# Smart Parking

## 1. Vấn đề xảy ra ở đâu?

Vấn đề xảy ra tại **khu vực bãi đỗ xe**, đặc biệt tại **cổng vào, cổng ra và khu vực quản lý số lượng xe trong bãi**.

Trong mô hình Smart Parking, bãi có **20 chỗ đỗ xe**. Người lái xe cần biết bãi còn bao nhiêu chỗ trống trước khi đi vào. Đồng thời, việc theo dõi số lượng xe vào/ra nếu thực hiện thủ công có thể gây sai sót và khó theo dõi lịch sử.

Hệ thống được xây dựng nhằm tự động phát hiện xe tại cổng vào và cổng ra, cập nhật số lượng xe trong bãi, tính số chỗ trống và hiển thị thông tin trên phần cứng cũng như Web Dashboard.

---

## 2. Ai gặp vấn đề?

### Người lái xe

- Khó biết chính xác bãi còn bao nhiêu chỗ trống.
- Có thể mất thời gian khi phải kiểm tra tình trạng bãi.
- Có thể gặp bất tiện nếu bãi đã đầy nhưng chưa biết trước.

### Nhân viên bảo vệ / quản lý bãi

- Phải theo dõi xe vào và xe ra.
- Phải kiểm tra số lượng xe và số chỗ còn trống.
- Việc đếm xe thủ công có thể xảy ra sai sót.
- Khó theo dõi lại lịch sử xe vào/ra nếu không có hệ thống lưu trữ.

### Chủ bãi xe

- Cần theo dõi tình trạng sử dụng bãi.
- Cần biết số lượng xe hiện tại.
- Cần theo dõi lịch sử xe vào/ra để phục vụ quản lý và thống kê.

---

## 3. Khi nào vấn đề xảy ra?

Vấn đề đặc biệt rõ ràng trong các trường hợp:

- Có nhiều xe vào và ra trong cùng khoảng thời gian.
- Vào giờ cao điểm, số lượng xe tăng.
- Nhân viên phải liên tục đếm xe bằng mắt.
- Cần biết chính xác số chỗ còn trống.
- Cần kiểm tra lại lịch sử xe vào/ra.
- Việc cập nhật số lượng xe được thực hiện thủ công.

---

## 4. Hiện tại họ xử lý bằng cách nào?

Đối với các bãi xe quy mô nhỏ, việc quản lý có thể được thực hiện bằng:

- Nhân viên quan sát và đếm xe.
- Ghi nhận xe vào/ra thủ công.
- Sử dụng vé hoặc phương thức ghi nhận truyền thống.
- Sử dụng bảng thông báo số chỗ trống và cập nhật thủ công.

Các phương pháp này tương đối đơn giản nhưng phụ thuộc nhiều vào con người. Khi số lượng xe tăng hoặc cần theo dõi dữ liệu trong thời gian dài, việc quản lý sẽ trở nên khó khăn hơn.

---

# 5. Điểm bất tiện, rủi ro hoặc tốn kém là gì?

### Bất tiện

- Người lái xe khó biết trước tình trạng bãi.
- Nhân viên phải liên tục theo dõi xe.
- Việc đếm xe mất thời gian.
- Khó tra cứu lịch sử xe vào/ra nếu chỉ ghi chép thủ công.

### Rủi ro

- Có thể đếm sai số lượng xe.
- Có thể cập nhật sai số chỗ trống.
- Có thể xảy ra sai lệch giữa số xe thực tế và số xe được ghi nhận.
- Dữ liệu lịch sử có thể bị thiếu hoặc nhầm nếu ghi chép thủ công.

### Tốn kém

- Cần nhân sự theo dõi và quản lý bãi.
- Chi phí nhân sự có thể tăng khi quy mô bãi lớn.
- Các hệ thống tự động hóa cao sử dụng camera hoặc AI có thể yêu cầu chi phí thiết bị và triển khai lớn hơn.

---

# 6. Giải pháp đề xuất

Xây dựng **Smart Parking IoT System** sử dụng ESP32, cảm biến siêu âm, MQTT, Server, SQLite và Web Dashboard để tự động theo dõi trạng thái bãi đỗ xe.

Hệ thống sử dụng **hai ESP32**:

- **ESP32 Entry:** quản lý cổng vào.
- **ESP32 Exit:** quản lý cổng ra.

Mỗi ESP32 sử dụng cảm biến **HC-SR04** để phát hiện xe.

Khi phát hiện xe:

- ESP32 Entry gửi sự kiện `IN`.
- ESP32 Exit gửi sự kiện `OUT`.
- MQTT Broker truyền dữ liệu giữa ESP32 và hệ thống Backend.
- `mqtt.js` xử lý sự kiện và cập nhật Database.
- Database lưu số lượng xe, số chỗ trống và lịch sử.
- Server cung cấp API cho Web.
- Web Dashboard hiển thị trạng thái bãi xe.

---

## 7. Mục tiêu của hệ thống

Mục tiêu chính của hệ thống là:

> **Tự động phát hiện xe --> gửi sự kiện IN/OUT --> cập nhật Database --> tính số chỗ trống --> cập nhật thiết bị --> hiển thị trên Web Dashboard.**

Cụ thể, hệ thống hướng tới:

- Tự động phát hiện xe vào.
- Tự động phát hiện xe ra.
- Điều khiển barrier bằng servo.
- Tự động cập nhật số lượng xe.
- Tự động tính số chỗ trống.
- Hiển thị số chỗ trống bằng TM1637.
- Sử dụng LED xanh/đỏ để thể hiện trạng thái còn chỗ hoặc đầy.
- Lưu lịch sử xe vào/ra.
- Hiển thị trạng thái và lịch sử trên Web Dashboard.

---

# 8. Quy mô hệ thống

Mô hình bãi xe có:

- **Tổng số chỗ:** 20.
- **Số xe trong bãi:** được cập nhật tự động.
- **Số chỗ trống:** được tính dựa trên số xe hiện tại.

Công thức:

```text
empty = total - cars
```

Trong đó:

```text
total = 20
cars  = số xe hiện tại
empty = số chỗ còn trống
```

Ví dụ:

| Số xe | Chỗ trống | Trạng thái |
|---:|---:|---|
| 0 | 20 | Còn chỗ |
| 5 | 15 | Còn chỗ |
| 10 | 10 | Còn chỗ |
| 19 | 1 | Sắp đầy |
| 20 | 0 | Bãi đầy |

---

# 9. Kiến trúc hệ thống

```text
SMART PARKING --> ESP32 ENTRY --> HC-SR04 --> Phát hiện IN --> Servo Entry --> MQTT Broker
SMART PARKING --> ESP32 EXIT  --> HC-SR04 --> Phát hiện OUT --> Servo Exit --> MQTT Broker

MQTT Broker --> mqtt.js --> SQLite Database
SQLite Database --> parking
SQLite Database --> history

SQLite Database --> mqtt.js --> MQTT (parking/status) --> ESP32 Entry --> TM1637
SQLite Database --> mqtt.js --> MQTT (parking/status) --> ESP32 Entry --> LED

SQLite Database --> server.js --> REST API --> app.js --> Web Dashboard
```

---

# 10. Các thành phần phần cứng

## ESP32 Entry

ESP32 tại cổng vào có nhiệm vụ:

- Đọc cảm biến HC-SR04.
- Phát hiện xe vào.
- Điều khiển servo mở/đóng barrier.
- Gửi sự kiện `IN` qua MQTT.
- Nhận số chỗ trống từ MQTT.
- Điều khiển LED trạng thái.
- Hiển thị số chỗ trống trên TM1637.

## ESP32 Exit

ESP32 tại cổng ra có nhiệm vụ:

- Đọc cảm biến HC-SR04.
- Phát hiện xe ra.
- Điều khiển servo barrier.
- Gửi sự kiện `OUT` qua MQTT.

## HC-SR04

Được sử dụng để đo khoảng cách giữa cảm biến và xe.

Trong chương trình, hệ thống sử dụng ngưỡng phát hiện:

```text
Khoảng cách < 15 cm --> phát hiện có xe
```

Sau khi xe đi khỏi vùng cảm biến:

```text
Khoảng cách > 30 cm --> cho phép phát hiện xe tiếp theo
```

## TM1637

TM1637 được sử dụng tại ESP32 Entry để hiển thị số chỗ trống.

Ví dụ:

```text
20 --> 19 --> 18 --> ... --> 1 --> 0
```

## LED

Hai LED thể hiện trạng thái bãi:

```text
Còn chỗ --> LED xanh ON --> LED đỏ OFF

Hết chỗ --> LED xanh OFF --> LED đỏ ON
```

---

# 11. Các công nghệ sử dụng

| Công nghệ | Vai trò |
|---|---|
| ESP32 | Bộ điều khiển tại cổng vào/ra |
| HC-SR04 | Phát hiện xe |
| Servo | Điều khiển barrier |
| TM1637 | Hiển thị số chỗ trống |
| LED | Hiển thị trạng thái bãi |
| Arduino IDE | Lập trình ESP32 |
| Wi-Fi | Kết nối ESP32 với mạng |
| MQTT | Giao tiếp giữa ESP32 và Backend |
| Mosquitto | MQTT Broker |
| Node.js | Chạy Backend |
| mqtt.js | Nhận và xử lý sự kiện MQTT |
| Express.js | Xây dựng REST API |
| SQLite | Lưu trữ dữ liệu |
| JavaScript | Xử lý dữ liệu và giao diện Web |
| HTML/CSS | Xây dựng Web Dashboard |

---

# 12. MQTT Topics

Hệ thống sử dụng các topic chính:

## Xe vào

```text
parking/entry
```

Message:

```text
IN
```

ESP32 Entry gửi khi phát hiện xe vào.

## Xe ra

```text
parking/exit
```

Message:

```text
OUT
```

ESP32 Exit gửi khi phát hiện xe ra.

## Trạng thái bãi

```text
parking/status
```

Message là số chỗ trống.

Ví dụ:

```text
19
```

Topic này được Backend gửi về ESP32 Entry để cập nhật TM1637 và LED.

---

# 13. Luồng xe vào

```text
Xe đến cổng vào --> HC-SR04 --> ESP32 Entry --> Kiểm tra chỗ trống --> Servo mở barrier --> MQTT (IN) --> MQTT Broker --> mqtt.js --> SQLite --> Cập nhật cars + 1, empty - 1 --> Lưu lịch sử --> MQTT (parking/status) --> ESP32 Entry --> TM1637 + LED
```

---

# 14. Luồng xe ra

```text
Xe đến cổng ra --> HC-SR04 --> ESP32 Exit --> Servo mở barrier --> MQTT (OUT) --> MQTT Broker --> mqtt.js --> SQLite --> Cập nhật cars - 1, empty + 1 --> Lưu lịch sử --> MQTT (parking/status) --> ESP32 Entry --> TM1637 + LED
```

---

# 15. Luồng dữ liệu Backend và Web

Sau khi ESP32 gửi `IN` hoặc `OUT`, `mqtt.js` xử lý dữ liệu.

## Database

Bảng `parking` lưu:

```text
id
total
cars
empty
```

Bảng `history` lưu:

```text
id
event
time
```

## MQTT.js

`mqtt.js`:

1. Kết nối MQTT Broker.
2. Subscribe `parking/entry`.
3. Subscribe `parking/exit`.
4. Nhận sự kiện `IN/OUT`.
5. Cập nhật bảng `parking`.
6. Lưu lịch sử vào bảng `history`.
7. Gửi số chỗ trống mới lên `parking/status`.

## Server.js

`server.js` cung cấp hai API:

```text
GET /status
GET /history
```

Trong đó:

```text
/status --> trạng thái hiện tại của bãi

/history --> lịch sử xe vào/ra
```

## App.js

`app.js` sử dụng `fetch()` để gọi API.

Web cập nhật dữ liệu định kỳ:

```text
Mỗi 2 giây --> lấy status mới --> lấy history mới --> cập nhật giao diện
```

---

# 16. Cấu trúc Database

## Bảng `parking`

```text
parking --> id
        --> total
        --> cars
        --> empty
```

Ví dụ:

```text
id    = 1
total = 20
cars  = 3
empty = 17
```

## Bảng `history`

```text
history --> id
        --> event
        --> time
```

Ví dụ:

```text
1    IN     2026-10-15 18:10:20
2    IN     2026-10-15 18:15:30
3    OUT    2026-10-15 18:20:45
```

---

# 17. Nguyên tắc cập nhật số lượng

## Khi xe vào

```text
cars = cars + 1
empty = empty - 1
```

Ví dụ:

```text
cars  = 5
empty = 15

XE VÀO

cars  = 6
empty = 14
```

## Khi xe ra

```text
cars = cars - 1
empty = empty + 1
```

Ví dụ:

```text
cars  = 6
empty = 14

XE RA

cars  = 5
empty = 15
```

Database có điều kiện giới hạn để tránh:

```text
cars < 0
```

hoặc:

```text
empty > total
```

---

# 18. Kết quả đạt được

Hệ thống mô hình đã thực hiện được các chức năng chính:

- Phát hiện xe tại cổng vào bằng HC-SR04.
- Phát hiện xe tại cổng ra bằng HC-SR04.
- Điều khiển barrier bằng servo.
- Gửi sự kiện xe vào/ra thông qua MQTT.
- Sử dụng Mosquitto làm MQTT Broker.
- Tự động cập nhật số lượng xe trong SQLite.
- Tự động cập nhật số chỗ trống.
- Lưu lịch sử xe vào/ra.
- Gửi trạng thái số chỗ trống về ESP32 Entry.
- Hiển thị số chỗ trống bằng TM1637.
- Hiển thị trạng thái còn chỗ/hết chỗ bằng LED.
- Cung cấp REST API bằng Express.js.
- Hiển thị trạng thái và lịch sử trên Web Dashboard.
- Web tự động cập nhật dữ liệu định kỳ.

---

# 19. Hạn chế của phiên bản hiện tại

Đây là mô hình thử nghiệm với quy mô nhỏ nên vẫn có một số hạn chế:

- HC-SR04 phát hiện xe dựa trên khoảng cách, chưa nhận diện loại xe.
- Chưa có camera nhận diện biển số.
- Chưa có hệ thống xác thực danh tính xe.
- Web Dashboard hiện tập trung vào trạng thái và lịch sử.
- Hệ thống sử dụng SQLite phù hợp với mô hình demo và quy mô nhỏ.
- MQTT Broker và Server hiện được triển khai trong môi trường mạng nội bộ phục vụ mô hình.

---

# 20. Hướng phát triển

Trong tương lai, hệ thống có thể mở rộng:

- Sử dụng camera để nhận diện biển số.
- Quản lý thông tin từng phương tiện.
- Xây dựng ứng dụng mobile.
- Giám sát bãi xe từ xa qua Internet.
- Lưu trữ dữ liệu trên Cloud.
- Thống kê số lượt xe theo ngày, tuần, tháng.
- Thống kê thời gian xe lưu trú.
- Tích hợp tính phí và thanh toán gửi xe.
- Mở rộng số lượng cổng và số lượng chỗ đỗ.
- Tích hợp AI để phân tích dữ liệu sử dụng bãi.

---

# 21. Kết luận

**Smart Parking IoT System** là mô hình ứng dụng IoT nhằm tự động hóa việc theo dõi và quản lý bãi đỗ xe.

Hệ thống kết hợp:

```text
ESP32 --> HC-SR04 --> Servo --> TM1637 --> LED --> Wi-Fi --> MQTT --> Mosquitto --> Node.js --> SQLite --> REST API --> Web Dashboard
```

để tạo thành một quy trình:

```text
Phát hiện xe --> Xác định IN / OUT --> Gửi MQTT --> Cập nhật Database --> Lưu lịch sử --> Cập nhật số chỗ trống --> Cập nhật ESP32 --> Cập nhật Web Dashboard
```

Qua mô hình này, hệ thống có thể minh họa cách các thiết bị IoT giao tiếp với Backend thông qua MQTT, cách Backend xử lý và lưu trữ dữ liệu, đồng thời cung cấp dữ liệu cho giao diện Web để giám sát trạng thái bãi xe theo thời gian gần thực.
