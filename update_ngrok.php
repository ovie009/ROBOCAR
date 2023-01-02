<?php

    if (isset($_POST["ip_address"]) && isset($_POST["ngrok_address"])) {
        # code...
        $ngrokAddress = $_POST["ngrok_address"];

        session_start();
        $_SESSION['ngrok_address'] = $ngrokAddress;
        $expiration = time() + 7200; // expiration date is two hours from now
        setcookie("ngrokAddress", $ngrokAddress);
        header("location: index.php");
        
    } else {
        # code...
        header("location: index.php?invalidBackDoor");
    }
    
?>