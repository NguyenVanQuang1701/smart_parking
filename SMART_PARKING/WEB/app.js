// Giao diện web, hiển thị trạng thái
const API =
"http://localhost:3000";



function loadStatus()   //Lấy trạng thái hiện tại của bãi xe từ server
{


fetch(API+"/status")    //Gửi request đến API /status

.then(res=>res.json())

.then(data=>{


document.getElementById("total").innerHTML =
data.total;


document.getElementById("cars").innerHTML =
data.cars;


document.getElementById("empty").innerHTML =
data.empty;



});


}




function loadHistory()      //Lấy lịch sử xe vào/ra từ server và hiển thị thành bảng trên Web
{


fetch(API+"/history")

.then(res=>res.json())

.then(data=>{


let html="";


data.forEach(item=>{            //Duyệt từng lịch sử


html += `

<tr>

<td>${item.id}</td>

<td>${item.event}</td>

<td>${item.time}</td>

</tr>

`;


});


document.getElementById("history").innerHTML=html;


});


}




loadStatus();

loadHistory();


// cập nhật mỗi 2 giây

setInterval(()=>{       //setInterval() dùng để lặp lại một đoạn code theo khoảng thời gian cố định

loadStatus();

loadHistory();


},2000);