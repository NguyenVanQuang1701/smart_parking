// API /status, /history -->Web lấy dữ liệu
const express=require("express");  //Thư viện express
const cors=require("cors");

const db=require("./database"); //import database.js

require("./mqtt");          //khởi động mqtt


const app=express();

app.use(cors());


app.get("/status",(req,res)=>{      //tạo api GET/ status


db.get(
"SELECT * FROM parking",
(err,row)=>{

res.json(row);

});


});



app.get("/history",(req,res)=>{


db.all(
"SELECT * FROM history ORDER BY id DESC",
(err,row)=>{

res.json(row);      //trả dữ liệu json lịch sử về web

});


});



app.listen(3000,()=>{       ////mở server tại port 3000

console.log(
"SERVER RUN PORT 3000"
);

});