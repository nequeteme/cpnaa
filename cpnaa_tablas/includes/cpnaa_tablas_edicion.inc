<?php

/*
 * Formulario para Editar las tablas de Cpnaa
 */
function cpnaa_tablas_edicion_form($form, &$form_state) {
  $inicial=false;
  $form = array();
  $form['#tree'] = TRUE;
  $form['form_edicion'] = array(
    '#type' => 'container','#prefix' => '<div id="form_edicion_wrapper">', '#suffix' => '</div>',
  );  
  if(empty($form_state['status'])){
    $form_state['status']="inicial";
    $form_state['table_select']='';
    $inicial=TRUE;
  }
  //Primera parte del formulario 
  if($inicial){
    $form['form_edicion']['table'] = array(
      '#type' => 'select',
      '#title' => t('Tabla'),
      '#options' => cpnaa_tablas_get_tablas_select(),
    );
    $form['form_edicion']['carga_submit'] = array(
      '#type' => 'submit',
      '#value' => t('Cargar'),
      '#submit' => array('cpnaa_tablas_edicion_carga'),
      '#ajax' => array(
        'callback' =>'cpnaa_tablas_carga_tabla_callback', 
        'wrapper' => 'form_edicion_wrapper',
      ),
    );
  }
  else{
    if($form_state['status']=="tabla"){
      $columns=cpnaa_tablas_get_tablas_schema($form_state['table_select']);
      $form['form_edicion']['data_table'] = array(
        '#type' => 'container','#prefix' => '<div class="form_edicion_table">', '#suffix' => '</div>',
      );
      //nombre de las columnas
      foreach ($columns as $key => $value) {
        $form['form_edicion']['data_table']['table_names_'.$key] = array(
	    '#markup' => $key,
	  	);	
      }
	  $query_data = db_select($form_state['table_select'], 'd');
	  $query_data->fields('d');              
	  $result_data = $query_data->execute(); 
	  dpm($result_data);
	  foreach ($result_data as $row) {
	  	foreach ($row as $key => $value) {
	  		$form['form_edicion']['data_table']['table_data_'.$key] = array(
		    	'#markup' => $value,
		  	);
		  }
	  }
	  
	  
	  
      $form['form_edicion']['cancelar_submit'] = array('#type' => 'submit', '#value' => t('Cancelar'),
        '#submit' => array('cpnaa_tablas_edicion_cancelar'),
        '#ajax' => array( 'callback' =>'cpnaa_tablas_carga_tabla_callback', 'wrapper' => 'form_edicion_wrapper', ),
      );
      $form['form_edicion']['Agregar_submit'] = array('#type' => 'submit', '#value' => t('Agregar registro'),
        '#submit' => array('cpnaa_tablas_edicion_agregar'), '#ajax' => array('callback' =>'cpnaa_tablas_carga_tabla_callback', 'wrapper' => 'form_edicion_wrapper', ),
      );
    }
	// agregar un registro a la tabla
    else if ($form_state['status']=="agregar") {
      $columns=cpnaa_tablas_get_tablas_schema($form_state['table_select']);
      $form['form_edicion']['add_table'] = array(
        '#type' => 'container','#prefix' => '<div class="form_edicion_add_table">', '#suffix' => '</div>',
      );
      //nombre de las columnas
      foreach ($columns as $key => $value) {
        if($value['type']=="varchar" ){
          $form['form_edicion']['add_table'][$key] = array('#type' => 'textfield', '#title' => $key,
              '#default_value' => $value["default"] , '#size' => 60, '#maxlength' => $value["length"] ,
              '#required' => TRUE,
          );
        }
        else if($value['type']=="int" ){
          $form['form_edicion']['add_table'][$key] = array('#type' => 'textfield', '#title' => $key,
              '#default_value' => $value["default"], '#size' => 10, '#maxlength' => "10",
              '#required' => TRUE, '#element_validate' => array('element_validate_integer_positive'),
          );
        }
      }
      $form['form_edicion']['cancelar_add_submit'] = array('#type' => 'submit', '#value' => t('Cancelar'),
        '#submit' => array('cpnaa_tablas_edicion_cancelar_add'),
        '#ajax' => array( 'callback' =>'cpnaa_tablas_carga_tabla_callback', 'wrapper' => 'form_edicion_wrapper', ),
      );
      $form['form_edicion']['Agregar_add_submit'] = array('#type' => 'submit', '#value' => t('Guardar'),
        '#submit' => array('cpnaa_tablas_edicion_agregar_add'), 
        '#ajax' => array('callback' =>'cpnaa_tablas_carga_tabla_callback', 'wrapper' => 'form_edicion_wrapper', ),
      );   
    }
  }
	
   
  return $form;
}

function cpnaa_tablas_carga_tabla_callback($form, $form_state) {
  return $form['form_edicion'];
}

function cpnaa_tablas_edicion_carga($form, &$form_state) {
  $form_state['status']="tabla";
  $form_state['table_select']=$form_state['values']['form_edicion']['table'];
  $form_state['rebuild'] = TRUE;
}
function cpnaa_tablas_edicion_agregar_add($form, &$form_state) {
	$columns=cpnaa_tablas_get_tablas_schema($form_state['table_select']);
	$data=FALSE;
	foreach ($columns as $key => $value) {
		$data[$key]=$form_state['values']['form_edicion']['add_table'][$key];
    }
	$query_create_cart = db_insert($form_state['table_select'])
      ->fields($data)
      ->execute();
  $form_state['status']="tabla";
  $form_state['rebuild'] = TRUE;
}

function cpnaa_tablas_edicion_cancelar_add($form, &$form_state) {
  $form_state['status']="tabla";
  $form_state['rebuild'] = TRUE;
}

function cpnaa_tablas_edicion_cancelar($form, &$form_state) {
  $form_state['status']="inicial";
  $form_state['table_select']='';
  $form_state['rebuild'] = TRUE;
}

function cpnaa_tablas_edicion_agregar($form, &$form_state) {
  $form_state['status']="agregar";
  $form_state['rebuild'] = TRUE;
}


/*
 * Metodo para retornar los datos de las tablas
 *
 * @return array con los datos para el select
 */
function cpnaa_tablas_get_tablas_schema($alias_tabla='departamento'){
  $data=false;
  global $CPNAA_tablas_names;
  $schema = drupal_get_schema($CPNAA_tablas_names[$alias_tabla]['table'],TRUE); 
  return $schema['fields'] ;
}