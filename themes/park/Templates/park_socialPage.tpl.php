<?php

echo 'from template';
//dpm(get_defined_vars());
//dpm($form);

// clear theme pointed to this file so it could be fully rendered by the default renderer
unset($form['#theme']);

echo render($form);
