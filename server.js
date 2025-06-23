const express = require('express');
const cors = require('cors');
const path = require('path');

const app = express();
app.use(cors()); // Cho phép CORS từ ESP32
app.use(express.static(__dirname)); // Cho phép truy cập index.html

let ledState = 0; // 0: tắt, 1: bật

// API cho ESP32 gọi: /update?status=1 hoặc status=0
app.post('/update', (req, res) => {
  const status = req.query.status;
  if (status === '0' || status === '1') {
    ledState = Number(status);
    console.log(`LED được cập nhật thành: ${ledState}`);
    res.send('Đã cập nhật trạng thái');
  } else {
    res.status(400).send('Trạng thái không hợp lệ');
  }
});

// API cho giao diện web gọi
app.get('/status', (req, res) => {
  res.json({ led: ledState });
});

app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'index.html'));
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`✅ Server chạy ở cổng ${PORT}`);
});