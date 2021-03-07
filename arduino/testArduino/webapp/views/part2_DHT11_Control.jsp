<%@ page language="java" pageEncoding="UTF-8" %>

<html>
<head>
 <title>테스트</title>
<!-- <script src="../resources/js/jquery-3.5.0.min.js"></script> -->
<script  src="http://code.jquery.com/jquery-latest.min.js"></script>
<!--  <script src="../resources/js/jquery.ajax-cross-origin.min.js"></script> -->
</head>
<body>
 <h1> 아두이노 온습도 & ajax 연결하기 </h1>
 <table>
 	<thead>
 		<tr>
 			<th>시간</th>
 			<th>습도</th>
 			<th>온도</th>
 		</tr>
 	</thead>
 	<tbody>
 	</tbody>
 </table>
 <br>
 <button type="button" id="checkDHT">온습도 확인하기</button>
 
 <script>
	$('#checkDHT').on('click', function(){
		$.ajax({
		  method: "GET",
		  url: "http://192.168.20.4/DHT11.cgi", /* 서버 요청 주소가 다르기 때문에 CORS 해결할 필요가 있음 */
		  dataType : "jsonp",
		  jsonpCallback : "callback", 
		  
		  success : function(data){
			  console.log(data);
			  
			  // 서버에 작성할 내용
			  var tr_data = $('<tr>');
			  var td_times = $('<td>').text(formatDate(new Date()));
			  var td_humi = $('<td>').text(data.Humidity + "%"); // 습도
			  var td_temp = $('<td>').text(data.Temperature + "C"); // 온도
			  
			  tr_data.append(td_times).append(td_humi).append(td_temp);
			  
			  $("table").append(tr_data);
			  
		  }, error : function(error, code, msg) {
			  console.log(error);
			  console.log(code);
			  console.log(msg);
		  }
		}); 
	});
	
	// 원하는 시간 정보로 형식을 변환
	function formatDate(date) {
	    var d = new Date(date),
	        month = '' + (d.getMonth() + 1),
	        day = '' + d.getDate(),
	        year = d.getFullYear();

	    if (month.length < 2) month = '0' + month;
	    if (day.length < 2) day = '0' + day;
	    
	    var hours = date.getHours();
		var minutes = date.getMinutes();
		var ampm = hours >= 12 ? 'pm' : 'am';
		
		hours = hours % 12;
		hours = hours ? hours : 12; // 0시를 12시로!
		minutes = minutes < 10 ? '0'+minutes : minutes;
		
		var strTime = hours + ':' + minutes + ' ' + ampm;
		
	    return [year, month, day].join('-') + " " + strTime;
	}
 </script>
 
</body>
</html>