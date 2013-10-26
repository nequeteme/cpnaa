<?php

/*
 * Formulario para Editar las tablas de Cpnaa
 */
function cpnaa_tablas_edicion_form() {
  $form = array();
  $form['#tree'] = TRUE;
  $form['form_edicion'] = array(
    '#type' => 'container','#prefix' => '<div class="form_edicion_wrapper">', '#suffix' => '</div>',
  );  
  if(!empty($form_state['status'])){
    $form_state['status']="inicial";
  }

  if($form_state['status']=="inicial"){
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
	
   
  return $form;
}

function cpnaa_tablas_carga_tabla_callback($form, $form_state) {
  return $form['form_edicion'];
}

function cpnaa_tablas_edicion_carga($form, &$form_state) {
  $form_state['status']="tabla";
  $form_state['rebuild'] = TRUE;
}
