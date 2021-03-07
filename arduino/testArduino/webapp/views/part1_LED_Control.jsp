<%@ page language="java" pageEncoding="UTF-8" %>
<html>
<head>
 <title>테스트</title>
</head>
<body>
 <h1> 아두이노 LED 연결하기 </h1>
 <form method="get" action="http://192.168.20.4/led.cgi">
 <!-- cgi (common gateway interface) :
 		사용자의 요구를 아두이노에게 돌려주기 위한 방법
 -->
 	<p>
 		RED
 		<input type="radio" name="LEDstatus" value="1" /> On / <input type="radio" name="LEDstatus" value="0" /> Off <br>
 	</p>
 	<input type="submit" value="전송하기">
 </form>
 
</body>
</html>