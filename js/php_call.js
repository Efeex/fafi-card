let status="TRUE";
let uid = "8888";
let log_uid;

phpCall()
/*
do {


  sleep(1);


} while(status=="TRUE"); //loop will run infinite
*/

function phpCall(){
  
  let myObj;

  let xmlhttp = new XMLHttpRequest();
  xmlhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
        myObj = JSON.parse(this.responseText);
        document.getElementById("demo").innerHTML = myObj.log_uid;
        log_uid = myObj.log_uid;
        console.log(log_uid)

        if(uid != log_uid){
          uid = log_uid
          console.log(uid)
          window.location.href = "php/switch.php?uid=" + uid;
        }

    }
  };
  xmlhttp.open("GET", "php/uid.php", true);
  xmlhttp.send();
};

phpCall();
