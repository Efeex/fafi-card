<?php

  include ("connect.php");

  $id ='';
  $nome ='';
  $cognome ='';
  $data ='';
  $email ='';


  if(isset($_POST['submit'])){
    $id = $_POST['id'];
    $nome = $_POST['nome'];
    $cognome = $_POST['cognome'];
    $gender = $_POST['gender'];
    if (isset($gender) && $gender=="femmina");
    elseif (isset($gender) && $gender=="maschio");
    $data = $_POST['date'];
    $email = $_POST['email'];

    $conn->query("update dati set uid='$id', nome='$nome', cognome='$cognome', data='$data', sesso='$gender', email='$email' where uid = '$id'");
    printf("Errormessage: %s\n", $conn->error);
    if(!$conn)
    { echo mysqli_error(); }
    else
    {
      echo "Successfully Inserted <br />";
      header("Location: ../index.html");
    }
  }
?>
