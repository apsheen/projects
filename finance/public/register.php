<?php
    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if((empty($_POST["username"])) || (empty($_POST["password"])))
        {
            apologize("Please make sure that all fields are filled!");
        }
            
        if(strcmp($_POST["password"], $_POST["confirmation"]) != 0)
        {
            apologize("Passwords do not match!");
        }

        if((!(empty($_POST["username"]))) && (!(empty($_POST["password"]))) && (strcmp($_POST["password"], $_POST["confirmation"]) == 0))
        {
            $user = CS50::query("INSERT INTO users (username, hash, cash) VALUES(?, ?, '100.0000')", $_POST["username"], password_hash($_POST["password"], PASSWORD_DEFAULT));
            
            if($user == false)
            {
                apologize("This username has been taken!");
            }

            else
            {
                $rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
                $_SESSION["id"] = $rows[0]["id"];
                header('Location: index.php');
            }
        }
    }
    
?>