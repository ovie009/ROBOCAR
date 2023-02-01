<?php

    if (isset($_POST["ip_address"]) && isset($_POST["ngrok_address"])) {
        # code...
        $ngrokAddress = $_POST["ngrok_address"];
        $ipAddress = $_POST["ip_address"];
        $streamMode = $_POST['stream_mode'];

        session_start();
        $_SESSION['ngrok_address'] = $ngrokAddress;
        $expiration = time() + 7200; // expiration date is two hours from now

        if ($streamMode == 'internet') {
            # code...
            setcookie("ngrokAddress", $ngrokAddress, $expiration);
        } else {
            # code...
            setcookie("ngrokAddress", 'http://'.$ipAddress, $expiration);
        }
        
        header("location: index.php");
        
    } else {
        # code...
        header("location: index.php?invalidBackDoor");
    }
    
?>