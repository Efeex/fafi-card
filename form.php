<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>fafi card</title>

    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.1/css/bootstrap.min.css" integrity="sha384-WskhaSGFgHYWDcbwN70/dfYBj47jz9qbsMId/iRN3ewGhXQFZCSftd1LZCfmhktB" crossorigin="anonymous">

    <script src="https://code.jquery.com/jquery-3.3.1.min.js" integrity="sha256-FgpCb/KJQlLNfOu91ta32o/NMZxltwRo8QtmkMRdAu8=" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.1/js/bootstrap.min.js" integrity="sha384-smHYKdLADwkXOn1EmN1qk/HfnUcbVRZyYmZ4qpPea6sjB/pTJ0euyQp0Mk8ck+5T" crossorigin="anonymous"></script>
    <script src="js/form.js"></script>
</head>
<body>
  <?php
    $uid = filter_input(INPUT_GET, 'uid_log', FILTER_SANITIZE_STRING);
   ?>

<div class="row">
    <div class="container">
  
        <form class="needs-validation" name="Dati_Utente" action="php/control_data.php" method="post" enctype="multipart/form-data" novalidate>
            <div class="form-grouo row">
              <h1 class="my-5" style="display:inline;">UID: </h1>
              <input type="text" class="form-control form-control-lg" name="id" value="<?php echo $uid ?>" required readonly="readonly">
            </div>
            <div class="form-group row">
                <label for="nome" class="col-sm-2 col-form-label col-form-label-lg">Nome</label>
                <div class="col-sm-10">
                    <input type="text" class="form-control form-control-lg" name="nome" placeholder="Inserisci qui il nome" required>
                    <div class="invalid-feedback">
                        Inserisci il nome del cliente.
                    </div>
                    <div class="valid-feedback">
                        Bel nome!
                    </div>
                </div>
            </div>
            <div class="form-group row">
                <label for="cognome" class="col-sm-2 col-form-label col-form-label-lg">Cognome</label>
                <div class="col-sm-10">
                    <input type="text" class="form-control form-control-lg" name="cognome" placeholder="Inserisci qui il cognome" required>
                    <div class="invalid-feedback">
                        Inserisci il cognome del cliente.
                    </div>
                    <div class="valid-feedback">
                        Un gran cognome!
                    </div>
                </div>
            </div>
            <div class="form-group row">
                <label for="date" class="col-sm-2 col-form-label col-form-label-lg">Nascita</label>
                <div class="col-sm-10">
                    <input type="date" class="form-control form-control-lg" name="date" required>
                    <div class="invalid-feedback ml-2">
                        Inserisci la data di nascita.
                    </div>
                </div>
            </div>
            <div class="form-group row">
                <label for="inlineRadioM" class="col-sm-2 col-form-label col-form-label-lg">Sesso</label>
                <div class="col-sm-10 py-2">
                    <div class="form-check form-check-inline">
                        <input class="form-check-input" type="radio" name="gender" value="maschio" required>
                        <label class="form-check-label" for="maschioRadio">Maschio</label>
                    </div>
                    <div class="form-check form-check-inline">
                        <input class="form-check-input" type="radio" name="gender" value="femmina" required>
                        <label class="form-check-label" for="femminaRadio">Femmina</label>
                        <div class="invalid-feedback ml-2">
                            Scegli un sesso.
                        </div>
                        <div class="valid-feedback ml-2">
                            Ottimo sesso.
                        </div>
                    </div>
                </div>
            </div>
            <div class="form-group row">
                <label for="email" class="col-sm-2 col-form-label col-form-label-lg">Email</label>
                <div class="col-sm-10">
                    <input type="email" class="form-control form-control-lg" name="email" placeholder="Inserisci qui il l'email">
                    <div class="valid-feedback ml-2">
                        È un campo opzionale, non tutti la hanno.
                    </div>
                </div>
            </div>
            <div class="row">
                <div class="container">
                    <button type="submit" name="submit" class="btn btn-lg btn-block btn-outline-success">Registra</button>
                </div>
            </div>
        </form>
    </div>
</div>


</body>
</html>
