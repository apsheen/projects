<?php
    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("buy_form.php", ["title" => "Buy"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if((empty($_POST["symbol"])) || (empty($_POST["shares"])))
        {
            apologize("Please make sure that you have filled all fields!");
        }
        
        else
        {
            $stock = lookup($_POST["symbol"]);
            
            if($stock == false)
            {
                apologize("Please make sure you have entered a valid symbol!");
            }
            
            $positive = preg_match("/^\d+$/", $_POST["shares"]);
            
            if($positive != true)
            {
                apologize("You cannot buy a negative or fraction amount of stocks!");
            }
            
            $cash = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
            
            if(($stock["price"] * $_POST["shares"]) > $cash[0]["cash"])
            {
                apologize("You can not afford that!");
            }
            
            CS50::query("INSERT INTO user_portfolio (user_id, symbol, stocks) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE stocks = stocks + VALUES(stocks)", $_SESSION["id"], $_POST["symbol"], $_POST["shares"]);
            CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $stock["price"] * $_POST["shares"], $_SESSION["id"]);
            CS50::query("INSERT INTO history (user_id, action, symbol, shares, price) VALUES(?, 'BUY', ?, ?, ?)", 
                $_SESSION["id"], $_POST["symbol"], $_POST["shares"], $stock["price"] * $_POST["shares"]);
            header('Location: index.php');
        }
    }

?>