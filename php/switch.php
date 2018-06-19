<?php


  include ("connect.php");
  /*
  exec("mode com7: BAUD=9600 PARITY=n DATA=8 STOP=1 to=off dtr=off rts=off");
  $fp =fopen("com7", "r+");
  //$fp = fopen('/dev/ttyUSB0','r+'); //use this for Linux
  $data = fread($fp, "10"); //write string to serial
  echo $data;
  fclose($fp); */

  $nome = "matteo";
  $sql = "SELECT nome FROM dati";
  $result = $conn->query($sql);

  if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
        echo "nome: " . $row["nome"]. " - cognome: " . $row["cognome"]. " - data: " . $row["data"]. "<br>";
        if ($row["nome"] == 'matteo') {
          header("Location: read.php");
        } else {
          //header("Location: ../index.html");
        }
    }
  } else {
      echo "0 results";
  }
?>
