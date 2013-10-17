<?php

/*
 * Formulario para importar datos por un csv
 */
function cpnaa_tablas_upload_csv_form() {
	
  $form = array();
	$form['table'] = array(
    '#type' => 'select',
    '#title' => t('Tabla:'),
    '#options' => $CPNAA_tablas_names,
  );
  $form['browser'] = array(
    '#type' => 'fieldset',
    '#title' => t('Subir Archivo'),
    '#collapsible' => TRUE,
    '#description' => t("Subir Archivo csv."),
  );
  $file_size = t('Tamaño maximo del Archivo: !size MB.', array('!size' => file_upload_max_size()));
  $form['browser']['file_upload'] = array(
    '#type' => 'file',
    '#title' => t('Archivo CSV'),
    '#size' => 40,
    '#description' => t('Seleccione un archivo CSV para importar los datos. ') . $file_size,
  );
 
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Importar'),
  );
  // set the form encoding type
  $form['#attributes']['enctype'] = "multipart/form-data";
  return $form;
}

/*
 * Validación del formulario de importación por csv
 */
function cpnaa_tablas_upload_csv_form_validate($form, &$form_state) {
  // attempt to save the uploaded file
  $file = file_save_upload('file_upload');
  // check file uploaded OK
  if (!$file) {
    form_set_error('file_upload', t('A file must be uploaded or selected from FTP updates.'));
  }
  else if($file->filemime != 'text/csv') {
    form_set_error('file_upload', t('The file must be of CSV type only.'));
  }
  else {
    // set files to form_state, to process when form is submitted
    $form_state['values']['file_upload'] = $file;
  }
}

/*
 * Subida de datos
 */
function cpnaa_tablas_upload_csv_form_submit($form, &$form_state) {
  $line_max = variable_get('user_import_line_max', 1000);
  ini_set('auto_detect_line_endings', true);
  $filepath = $form_state['values']['file_upload']->filepath;
  $handle = @fopen($filepath, "r");
  // start count of imports for this upload
  $send_counter = 0;
  while ($row = fgetcsv($handle, $line_max, ',')) {
    // $row is an array of elements in each row
    // e.g. if the first column is the email address of the user, try something like
    $mail = $row[0];
  }
}
