var express = require('express');
var app = express();
const path = require('path');
const { SerialPort } = require('serialport')
const { ReadlineParser } = require('@serialport/parser-readline')

var message_telo = "1-0-0-0-0";
var message_spicka = "0-0-0-0-0";
var update_time = new Date();

const port = new SerialPort({
    path: 'COM8',
    baudRate: 9600,
})
const parser = port.pipe(
    new ReadlineParser({ delimiter: '\n' })
);

parser.on('data', data =>{
    console.log(data);
    var splitted_result = data.split("-");
    update_time = new Date();
    //console.log(splitted_result);
    if(splitted_result[0] == "0"){
        message_spicka = data;
    }else if(splitted_result[0] == "1"){
        message_telo = data;
    }
});


app.get('/', function (req, res) {
        res.sendFile(path.join(__dirname, '/index.html'));
})
app.get('/web.js', function (req, res) {
    res.sendFile(path.join(__dirname, '/web.js'));
})
app.get('/data', function (req, res) {
    res.send({"message_spicka": (message_spicka + "-" + update_time.getHours() + ":" + update_time.getMinutes() + ":" + update_time.getSeconds()), "message_telo":(message_telo + "-" + update_time.getHours() + ":" + update_time.getMinutes() + ":" + update_time.getSeconds())});
    res.end();
})


var server = app.listen(8081, function () {
   var host = server.address().address
   var port = server.address().port
   console.log("Example app listening at http://%s:%s", host, port)
})