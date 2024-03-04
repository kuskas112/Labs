<!DOCTYPE html>
<html>
	<?php include("header.php"); ?>
	<body>
		
		<header>
			Electric Car Blog
		</header>

		
		<?php 
		include("menu.php");
		include("content.php");
		include($page);
		?>


		<?php include("footer.php"); ?>
	</body>
</html>
