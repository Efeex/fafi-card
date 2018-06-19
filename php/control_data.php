<?php

  include ("connect.php");

  $nome ='';
  $cognome ='';
  $data ='';
  $email ='';


  if(isset($_POST['submit'])){
    $nome = $_POST['nome'];
    $cognome = $_POST['cognome'];
    $gender = $_POST['gender'];
    if (isset($gender) && $gender=="femmina");
    elseif (isset($gender) && $gender=="maschio");
    $data = $_POST['date'];
    $email = $_POST['email'];

    $conn->query("insert into dati (nome, cognome, data, sesso, email) values('$nome', '$cognome', '$data', '$gender', '$email')");
    printf("Errormessage: %s\n", $conn->error);
    if(!$conn)
    { echo mysqli_error(); }
    else
    {
      echo "Successfully Inserted <br />";

    }
  }
?>
