const mqtt = require('mqtt')
const client = mqtt.connect("mqtt:broker.hivemq.com")

// Create mysql connection
var mysql = require('mysql');
var conn = mysql.createConnection({
    host    : 'localhost',
    user    : 'root',
    password: 'root',
    database: 'iot',
});

//kết nối.
conn.connect(function (err){
    //nếu có nỗi thì in ra
    if (err) throw err.stack;
    //nếu thành công
    function addRowTime(time1,temp1,humi1,voltage1,dust1) {
      let sql = `INSERT INTO Hyper(Time,Temp,Humi,Voltage,Dust) VALUES ('${time1}', '${temp1}','${humi1}','${voltage1}','${dust1}')`;
      conn.query(sql, function (err,results, fields) {
          if (err) throw err;
      });
    }
    function checkTime(i) {
      if (i < 10) {
          i = "0" + i;
      }
      return i;
    }
    
    // Hàm khởi tạo đồng hồ
    function startTime() {
      // Lấy Object ngày hiện tại
      var today = new Date();
    
      // Giờ, phút, giây hiện tại
      var h = today.getHours();
      var m = today.getMinutes();
      var s = today.getSeconds();
    
      // Chuyển đổi sang dạng 01, 02, 03
      h = checkTime(h);
      m = checkTime(m);
      s = checkTime(s);
      var t123 = h + ":" + m + ":" + s
      // Ghi ra trình duyệt
      return t123;
    }
    // Create mqtt 
    client.on('connect', () => {
      client.subscribe('Toan123456')
    })

    client.on('message', (topic, message) => {
      if(topic === 'Toan123456') {
        data = message.toString()
        data1 = JSON.parse(data)
        temp = data1['Temp']
        hum = data1['Humi']
        vol = data1['Voltage']
        dust = data1['Dust']
        a = startTime()
        addRowTime(a,temp,hum,vol,dust)
      }
  })
});