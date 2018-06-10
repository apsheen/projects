<?php
    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("sell_form.php", ["title" => "Sell"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if(empty($_POST["symbol"]))
        {
            apologize("Please make sure that you enter a symbol!");
        }
        
        else
        {
            $stock = lookup($_POST["symbol"]);
            
            if($stock == false)
            {
                apologize("Please make sure you have entered a valid symbol!");
            }
            
            else
            {
                $total_stocks = 0;
                $shares = CS50::query("SELECT stocks FROM user_portfolio WHERE symbol = ? AND user_id = ?", $_POST["symbol"], $_SESSION["id"]);
                
                foreach ($shares as $share)
                {
                    $total_stocks = $total_stocks + $share["stocks"];
                }
                
                CS50::query("DELETE FROM user_portfolio WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
                CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $total_stocks * $stock["price"], $_SESSION["id"]);
                CS50::query("INSERT INTO history (user_id, action, symbol, shares, price) VALUES(?, 'SELL', ?, ?, ?)", 
                    $_SESSION["id"], $_POST["symbol"], $total_stocks, $stock["price"] * $total_stocks);
                header('Location: index.php');
            }
        }
    }
    
?>