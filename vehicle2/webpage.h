const char mainPage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width = device-width initial-scale = 1.0">
    <title>Vehicle 1.0</title>
	<style>
	*{
  margin: 0;
  padding: 0;
  box-sizing: border-box;
  outline: none;
}
html{
  -moz-user-select: none; /* Firefox */
  -ms-user-select: none; /* Internet Explorer */
  -khtml-user-select: none; /* KHTML browsers (e.g. Konqueror) */
  -webkit-user-select: none; /* Chrome, Safari, and Opera */
  -webkit-touch-callout: none; /* Disable Android and iOS callouts*/
}
body{
  font-family: Montserrat, monospace;
  background-color: #101415;
}

a,a:focus,a:visited,a:hover{
	text-decoration:none;
}
/* header */
.header{

    padding: 25px 15px 10px 15px;
}

.header p{
  color: #FFF;
  font-size: 30px;
  text-align: center;
}
/* End of header */

/*  content  */
.content-lg{
  padding: 0 40px 0 40px;
}
.col-lg{
  position: relative;
  float: left;
  width: 25%;
  padding: 20px;
}
.col-lg-2{
  position: relative;
  float: left;
  width: 50%;
  padding: 20px;
}

.tab{
  display:block;
  width:100%;
  height: 150px;
  border-radius: 10px;
  padding: 5px;
}

.pryText{
  color: #FFF;
  font-size: 24px;
  padding-right :10px;
}

.pryTextVal{
  color: #FFF;
  font-size: 24px;
  padding-left:10px;
}

.tab-2{
  width:100%;
  height: 350px;
  border-radius: 10px;
  padding: 5px;
}

.tab-title{
  display:table;
  margin-top:5px;
  margin-left:5px;
  text-align: left;
  color: #FFF;
  font-size: 24px;
  letter-spacing: 1.2px;
}
.bgColorGray{
  background-color: #726D68;
}

.bgColorOlive{
  background-color: #4B5B3B;
}
.controller-black{
  background-color: #273938;
}
.arm-controller-black{
  background-color: #29303A;
}
.tab-slider{
  display: table;
  margin: 0 auto;
  padding: 10px 0 0 0;
}

.tab-range{
  display:table;
  margin:0 auto;
  position: relative;
  padding: 10px;
}
/*  controller  */
.controller-row1{
display: table;
margin: 0 auto;
}

.controller-row2{
  padding: 20px 0;
  display: table;
  margin: 0 auto;
}
.col-1{
  margin-right: 20px;
}

.col-3{
  margin-left: 18px;
}
#forward{
  background-color: #c4c4c4;
  width:50px;
  height:50px;
  border:none;
  border-radius: 25px 25px 5px 5px;
  transition: 0.3s;
}
#forward:hover{
  background-color:#726d68;
  color:#FFF;
}
#left{
  background-color: #c4c4c4;
  width:50px;
  height:50px;
  border:none;
  border-radius: 25px 5px 5px 25px;
  transition: 0.3s;
}
#left:hover{
  background-color:#726d68;
  color:#FFF;
}
#stop{
  background-color: #c4c4c4;
  font-size:16px;
  color: #cf1b1b;
  width:50px;
  height:50px;
  border:none;
  border-radius: 25px;
  transition: 0.3s;
}
#stop:hover{
  background-color:#726d68;
  color:#FFF;
}
#right{
  background-color: #c4c4c4;
  width:50px;
  height:50px;
  border:none;
  border-radius: 5px 25px 25px 5px;
  transition: 0.3s;
}
#right:hover{
  background-color:#726d68;
  color:#FFF;
}
#backword{
  background-color: #c4c4c4;
  width:50px;
  height:50px;
  border:none;
  border-radius: 5px 5px 25px 25px;
  transition: 0.3s;
}
#backword:hover{
  background-color:#726d68;
  color:#FFF;
}
.speed-controller-row{
  display: table;
  width:80%;
  margin:20px auto;
}
.arm-controller-row{
  display: table;
  width:95%;
  padding: 10px;
  margin:10px auto;
}
.regularWhite{
  color:#FFF;
  font-size:18px;
  margin-right:10px;
}

.slider {
  -webkit-appearance: none;
  width: 75%;
  height: 10px;
  border-radius: 5px;
  background: #d3d3d3;
  outline: none;
  opacity: 0.7;
  transition: opacity .2s;
}

.slider:hover {
  opacity: 1;
}

.slider::-webkit-slider-thumb {
  -webkit-appearance: none;
  appearance: none;
  width: 20px;
  height: 20px;
  border-radius: 50%;
  cursor: pointer;
  border: none;
}

.slider::-moz-range-thumb {
  width: 20px;
  height: 20px;
  border-radius: 50%;
  cursor: pointer;
  border: none;
}
.grab-button{
  display: table;
  padding-top:10px;
  width:80%;
  margin:0 auto;
}
#grab{
  background-color: #C4C4C4;
  position: relative;
  float: right;
  clear:both;
  width:60px;
  height: 60px;
  border:none;
  border-radius: 50%;
  transition: 0.3s;
}
#grab:hover{
  background-color: #726D68;
  color: #FFF;
}

.slider-green::-webkit-slider-thumb {
  background-color: #a2f371;
}
.slider-green::-moz-range-thumb{
  background-color: #a2f371;
}

.slider-blue::-webkit-slider-thumb {
  background-color: #22d2f9;
}
.slider-blue::-moz-range-thumb{
  background-color: #22d2f9;
}

.slider-orange::-webkit-slider-thumb {
  background-color: #f2c94c;
}
.slider-orange::-moz-range-thumb{
  background-color: #f2c94c;
}

.slider-orange2::-webkit-slider-thumb {
  background-color: #ffa931;
}
.slider-orange2::-moz-range-thumb{
  background-color: #ffa931;
}

/*  End of controller  */
/*  End of content  */


/*  Responsive Design  */


@media(max-width: 1130px){

.col-sm{
  padding:10px;
  width: 50%;
}
.col-sm-2{
  width:100%;
  padding: 10px;
}
.content-sm{
  padding: 0 20px 0 20px;
}


.tab-title{
  font-size: 15px;
  letter-spacing: 1px;
  margin-top: 10px;
}

.pryText{
  font-size: 15px;
}

#forward{
  width: 60px;
  height:60px;
  border-radius: 30px 30px 5px 5px;
  border:none;
  transition: 0.2s;
}
#forward:active{
  transform:scale(0.98);
}
#left{
  width: 60px;
  height:60px;
  border-radius: 30px 5px 5px 30px;
  border:none;
  transition: 0.2s;
}
#left:active{
  transform:scale(0.98);
}
#right{
  width: 60px;
  height:60px;
  border-radius: 5px 30px 30px 5px;
  border:none;
  transition: 0.2s;
}
#right:active{
  transform:scale(0.98);
}
#stop{
  width: 60px;
  height:60px;
  border-radius: 30px;
  border:none;
  transition: 0.2s;
}
#stop:active{
  transform:scale(0.98);
}
#backword{
  width: 60px;
  height:60px;
  border-radius: 5px 5px 30px 30px;
  border:none;
  transition: 0.2s;
}
#backword:active{
  transform:scale(0.98);
}
#grab:active{
  transform:scale(0.98);
}
}
/*  End of Responsive Design  */

	</style>
  </head>
  <body>

    <div class="header">
        <p>Vehicle 1.0</p>
    </div>
    <div class="content-lg content-sm">
      <div class="col-lg col-sm">
        <div class="tab bgColorGray">
          <span class="tab-title" id="temp">Temp: </span>
          <span class="tab-title" id="pressure">Pa: </span>
          <span class="tab-title" id="humid">Humid: </span>
          <span class="tab-title" id="rain">Rain: </span>
        </div>
      </div>
      <div class="col-lg col-sm">
        <div class="tab bgColorOlive">
          <span class="tab-title">Obsticle</span>
          <span class="tab-title" id="front">Front: </span>
          <span class="tab-title" id="altitude">Alt: </span>
          
        </div>
      </div>
      <div class="col-lg col-sm">
        <div class="tab bgColorGray">
          <span class="tab-title">Gas Sensors</span>
          <span class="tab-title" id="mq2">CO2:</span>
          <span class="tab-title" id="mq5">H2:</span>
        </div>
      </div>
      <div class="col-lg col-sm">
		<a id="gpsLink" href="#">
			<span class="tab bgColorOlive">
			  <span class="tab-title">GPS</span>
			  <span class="tab-title" id="latitude">Lat: </span>
			  <span class="tab-title" id="longitude">Long: </span>
			</span>
		</a>
      </div>
      <div class="col-lg-2 col-sm-2">
        <div class="tab-2 controller-black">
          <span class="tab-title">vehicle</span>
          <div class="controller-row1">
            <button id="forward" onclick="vehicle('f')">F</button>
          </div>
          <div class="controller-row2">
            <span class="col-1"><button id="left" onclick="vehicle('l')">L</button></span>
            <span class="col-2"><button id="stop" onclick="vehicle('s')">Stop</button></span>
            <span class="col-3"><button id="right" onclick="vehicle('r')">R</button></span>
          </div>
          <div class="controller-row1">
            <button id="backword" onclick="vehicle('b')">B</button>
          </div>
		  <div class="speed-controller-row"><span class="regularWhite">S</span>
            <input class="slider slider-orange2" type="range" min="0" max="90" value="0" onchange="arm('S', this.value)">
          </div>
        </div>
      </div>
      <div class="col-lg-2 col-sm-2">
        <div class="tab-2 arm-controller-black">
          <span class="tab-title">ARM</span>
          <div class="arm-controller-row"><span class="pryText">P</span>
            <input id="Spitch" class="slider slider-green" type="range" min="125" max="375" value="125" onchange="arm('P',this.value)" oninput="armAssign('P',this.value)"><span class="pryTextVal" id="pitchVal">0</span>
          </div>
          <div class="arm-controller-row"><span class="pryText">R</span>
            <input id="Sroll" class="slider slider-blue" type="range" min="80" max="335" value="80" onchange="arm('R',this.value)" oninput="armAssign('R',this.value)"><span class="pryTextVal" id="rollVal">0</span>
          </div>
		  <div class="arm-controller-row"><span class="pryText">K</span>
            <input id="Sroll2" class="slider slider-blue" type="range" min="100" max="335" value="173" onchange="arm('K',this.value)" oninput="armAssign('K',this.value)"><span class="pryTextVal" id="kVal">0</span>
          </div>
          <div class="arm-controller-row"><span class="pryText">Y</span>
            <input id="Syaw" class="slider slider-orange" type="range" min="202" max="386" value="291" onchange="arm('Y',this.value)" oninput="armAssign('Y',this.value)"><span class="pryTextVal" id="yawVal">0</span>
          </div>
          <div class="grab-button">
            <button id="grab" onclick="vehicle('G')">grab</button>
          </div>
        </div>
      </div>
  </div>
  
    <script>
		var Socket;
		function init(){
		  Socket  = new WebSocket('ws://' + window.location.hostname + ':81/');
			  Socket.onmessage = function(event){
				 json = JSON.parse(event.data);
				 document.getElementById("latitude").innerHTML = "Lat: "+json.latitude;
				 document.getElementById("longitude").innerHTML = "Long: "+json.longitude;
				 document.getElementById("gpsLink").href= "https://www.google.com/maps/search/?api=1&query="+json.latitude+","+json.longitude;
				 document.getElementById("temp").innerHTML = "Temp: "+json.temp;
				 document.getElementById("pressure").innerHTML = "Pa: "+json.pressure;
				 document.getElementById("humid").innerHTML = "Humid: "+json.humid;
				 document.getElementById("altitude").innerHTML = "Alt: "+json.altitude;
				 document.getElementById("mq2").innerHTML = "CO2: "+json.mq2;
				 document.getElementById("mq5").innerHTML = "H2: "+json.mq5;
				 document.getElementById("rain").innerHTML = "Rain: "+json.rain;
				 document.getElementById("front").innerHTML = "Front: "+json.distance;
			  }
		}
		function vehicle(dir){
		  Socket.send(dir);
		  console.log(dir);
		}
		
		function arm(h, val){
			Socket.send(h+val);
			console.log(h+val);
		}
		function armAssign(h, val){
			if(h==='P'){
				document.getElementById("pitchVal").innerHTML = Math.round(mapFn(val, 125,375,0,180));
			}
			else if(h==='R'){
				document.getElementById("rollVal").innerHTML = Math.round(mapFn(val, 80,335,0,180));
			}
			else if(h==='K'){
				document.getElementById("kVal").innerHTML = Math.round(mapFn(val, 100,335,0,180));
			}
			else{
				document.getElementById("yawVal").innerHTML = Math.round(mapFn(val, 202,386,40,140));
			}
		}
		function mapFn(val, a,b,c,d){
			return ((val-a)*(d-c)/(b-a))+c;
		}
		document.addEventListener('DOMContentLoaded', init, false);
	</script>
  </body>
</html>)=====";