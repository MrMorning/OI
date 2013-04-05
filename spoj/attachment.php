<?php
/**
 * The template for displaying attachments.
 *
 * @package WordPress
 * @subpackage Twenty_Ten
 * @since Twenty Ten 1.0
 */

get_header(); ?>

		<div id="container" class="single-attachment">
			<div id="content" role="main">

			<?php
			/* Run the loop to output the attachment.
			 * If you want to overload this in a child theme then include a file
			 * called loop-attachment.php and that will be used instead.
			 */
			get_template_part( 'loop', 'attachment' );
			?>
	<?php
$wud = wp_upload_dir();
$upload_path = $wud['basedir'];
$upload_url = $wud['baseurl'];
$path = wp_get_attachment_url($post->ID);
if (preg_match('#^' . $upload_url . '#', $path)) {
	$path = preg_replace('#^' . $upload_url . '#', $upload_path, $path);
	if (is_file($path)) {
		$map = array(
			'c'		=> 'cpp',
			'cpp'	=> 'cpp',
			'hs'	=> 'haskell',
			'pl'	=> 'perl',
			'php'	=> 'php',
			'txt'	=> 'plain',
			'xml'	=> 'xml',
			'html'	=> 'xml',
		);
		$ext = pathinfo($path, PATHINFO_EXTENSION);
		if (array_key_exists($ext, $map)) {
			$type = $map[$ext];
			$content = file_get_contents($path);
			echo apply_filters('the_content', '['.$type.']'.$content.'[/'.$type.']');
		}
	}
}
?>
			</div><!-- #content -->
		</div><!-- #container -->

<?php get_footer(); ?>

