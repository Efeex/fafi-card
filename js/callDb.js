$.getJSON ({
    type: "POST",
    url: 'your_functions_address.php',
    dataType: 'json',
    succes: function () {
        alert("yuppi")
    }
})