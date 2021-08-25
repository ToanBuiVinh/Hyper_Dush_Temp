var app = require('express')();
app.set('views', __dirname + '/views');
app.set('view engine', 'ejs');
var http = require('http').createServer(app);
// http
// var io = require('socket.io')(http); // socket
// Create mysql connection
var mysql = require('mysql');
var conn = mysql.createConnection({
  host: 'localhost',
  user: 'root',
  password: 'root', 
  database: 'iot',
});

conn.connect(function (err) {
  app.get('/', function (req, res) { // Handle http req
    //nếu có nỗi thì in ra
    if (err) throw err.stack;
    //nếu thành công
    let sql = `SELECT * FROM Hyper`;
    conn.query(sql, function (err, results, fields) {
      var time1 = []
      var temp1 = []
      var humi1 = []
      var voltage1 = []
      var dust1 = []
      for (let i = 0 ; i < results.length; i++){
        time1.push(results[i]['Time'])
        temp1.push(results[i]['Temp'])
        humi1.push(results[i]['Humi'])
        voltage1.push(results[i]['Voltage'])
        dust1.push(results[i]['Dust'])
      }
    res.render('socket', {time2: JSON.stringify(time1),temp2: JSON.stringify(temp1),humi2: JSON.stringify(humi1),voltage2: JSON.stringify(voltage1),dust2: JSON.stringify(dust1)});
    });
  });
})

// io.on('connection', function (socket) {
//   socket.on("Client-sent-data", function (data) {
//     //sau khi lắng nghe dữ liệu, server phát lại dữ liệu này đến các client khác
//     socket.emit("Server-sent-data", data);
//   });
// });

http.listen(3000, function () {
  console.log('listening on *:3000');
});
