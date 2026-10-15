// Tạo DB và tại bảng, lưu số xe/ chỗ trống/ lịch sử
const sqlite3 = require("sqlite3").verbose();


const db = new sqlite3.Database("parking.db");


db.serialize(()=>{

db.run(`
CREATE TABLE IF NOT EXISTS parking(
id INTEGER PRIMARY KEY,
total INTEGER,
cars INTEGER,
empty INTEGER
)
`);

// AUTOINCREMENT: tự tăng id
db.run(`
CREATE TABLE IF NOT EXISTS history(
id INTEGER PRIMARY KEY AUTOINCREMENT,  
event TEXT,
time DATETIME DEFAULT (datetime('now','localtime'))
)
`);



db.get(
"SELECT * FROM parking",
(err,row)=>{
// Nếu chưa có dữ liệu sẽ tạo
if(!row)
{
db.run(
"INSERT INTO parking(total,cars,empty) VALUES(20,0,20)"
);
}

});


});


module.exports=db;