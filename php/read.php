<?php
  include ("connect.php");

  $sql = "SELECT nome, cognome, data, sesso, email FROM dati";
  $result = $conn->query($sql);
  if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
        echo "nome: " . $row["nome"]. " - cognome: " . $row["cognome"]. " - data: " . $row["data"]. "<br>";
    }
} else {
    echo "0 results";
}
$conn->close();


 ?>
