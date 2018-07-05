let status="TRUE";
let uid = "00000";
let log_uid;
let log_time;

phpCall()



function phpCall(){

  let myObj;

  let xmlhttp = new XMLHttpRequest();
  xmlhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
        myObj = JSON.parse(this.responseText);
        document.getElementById("demo").innerHTML = myObj.log_uid;
        log_uid = myObj.log_uid;
        log_time = myObj.log_time;
        console.log(log_time)

        if(uid != log_uid){
          uid = log_uid
          console.log(uid)
          window.location.href = "php/switch.php?uid=" + uid;
        } else(
          phpCall()
        )

    }
  };
  xmlhttp.open("GET", "php/uid.php", true);
  xmlhttp.send();
};
