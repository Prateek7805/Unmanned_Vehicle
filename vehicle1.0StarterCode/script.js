var Socket;
function init(){
  Socket  = new WebSocket('ws://' + window.location.hostname + ':81/');
      Socket.onmessage = function(event){
        console.log(event.data);
      }
}
function vehicle(dir){
  Socket.send(dir);
  console.log(dir);
}
function arm(angle, val){
  Socket.send(angle+val);
}
document.addEventListener('DOMContentLoaded', init, false);
