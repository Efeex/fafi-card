<?php
  include ("connect.php");

  $uid = filter_input(INPUT_GET, 'uid_log', FILTER_SANITIZE_STRING);

  $sql = "SELECT uid, nome, cognome, data, sesso, email FROM dati";
  $result = $conn->query($sql);
  if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {

        if($row["uid"] == $uid){
          echo "uid: " . $row["uid"]. "nome: " . $row["nome"]. " - cognome: " . $row["cognome"]. " - data: " . $row["data"]. " - sesso: " . $row["sesso"]. " - email: " . $row["email"]. "<br>";
        }
    }
} else {
    echo "0 results";
}
$conn->close();


 ?>
