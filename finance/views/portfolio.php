<table>
    <tr>
        <td style = "width: 400px" >Name</td>
        <td style = "width: 400px">Symbol</td>
        <td style = "width: 400px">Shares</td>
        <td style = "width: 400px">Price per share</td>
        <td style = "width: 400px">Total</td>
    </tr>
    
    <tr>
        <td>CASH</td>
        <td></td>
        <td></td>
        <td></td>
        <td>$<?= number_format($cash[0]["cash"], 2) ?></td>
    </tr>

<?php foreach ($positions as $position): ?>

    <tr>
        <td><?= $position["name"] ?></td>
        <td><?= $position["symbol"] ?></td>
        <td><?= $position["stocks"] ?></td>
        <td>$<?= number_format($position["price"]) ?></td>
        <td>$<?= $position["price"] * $position["stocks"] ?></td>
    </tr>

<?php endforeach ?>
</table>
