<?php

function cpnaa_vprof_tramite_oficina_form($form, &$form_state) {
  $inicial=false;
  $form = array();
  $form['#tree'] = TRUE;
  $form['form_edicion'] = array(
    '#type' => 'container','#prefix' => '<div id="form_edicion_wrapper">', '#suffix' => '</div>',
  );  
  //estado del formulario en el ajax
  if(empty($form_state['status'])){
    $form_state['status']="inicial";    
    $inicial=TRUE;
  }
  //Primera parte del formulario 
  if($inicial){
  	$form['form_edicion']['texto_inicial'] = array(
         '#markup' => t('Permitir al usuario interno de CPNAA diligenciar los datos requeridos para generar un Certificado de Vigencia Profesional Digital, que permita'), '#prefix' => '<div class="texto_inicial">', '#suffix' => '</div>',
    );
    $form['form_edicion']['identificacion'] = cpnaa_user_form_identificacion();
    $form['form_edicion']['numdocu']= cpnaa_user_form_documento();
    $form['form_edicion']['cancelar_inicial'] = array(
      '#type' => 'submit',
      '#value' => t('Cancelar'),
      '#submit' => array('cpnaa_vprof_tramite_oficina_incial_cancelar'),
      '#ajax' => array(
        'callback' =>'cpnaa_vprof_tramite_oficina_callback', 
        'wrapper' => 'form_edicion_wrapper',
      ),
    );
    $form['form_edicion']['verificar_inicial'] = array(
      '#type' => 'submit',
      '#value' => t('Verificar'),
      '#submit' => array('cpnaa_vprof_tramite_oficina_incial_verificar'),
      '#ajax' => array(
        'callback' =>'cpnaa_vprof_tramite_oficina_callback', 
        'wrapper' => 'form_edicion_wrapper',
      ),
    );
  }
  else{
    if($form_state['status']=="datos_usuarios"){
    	$form['form_edicion']['texto_inicial'] = array(
         '#markup' => t('Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation'), '#prefix' => '<div class="texto_usuarios">', '#suffix' => '</div>',
    	);
    	$form['form_edicion']=cpnaa_vprof_form_usuario();
      $form['form_edicion']['cancelar_submit'] = array('#type' => 'submit', '#value' => t('Cancelar'),
        '#submit' => array('cpnaa_vprof_tramite_oficina_usuario_cancelar'),
        '#ajax' => array( 'callback' =>'cpnaa_vprof_tramite_oficina_callback', 'wrapper' => 'form_edicion_wrapper', ),'#weight' => 5,
      );
      $form['form_edicion']['continuar_submit'] = array('#type' => 'submit', '#value' => t('Continuar'),'#weight' => 5,
        '#submit' => array('cpnaa_vprof_tramite_oficina_usuario_continuar'), '#ajax' => array('callback' =>'cpnaa_vprof_tramite_oficina_callback', 'wrapper' => 'form_edicion_wrapper', ),
      );
    }
	// agregar un registro a la tabla
    else if ($form_state['status']=="pago_oficina") {
    	$banco=cpnaa_tablas_get_select('banco');
		  $form['form_edicion']['Banco'] = array(
		      '#type' => 'select',
		      '#title' => t('Banco'),
		      '#options' => $deptos,  
		  );
		  $form['form_edicion']['consignacion']= array(
    	'#type' => 'textfield', 
    	'#title' => t('Consignacion Numero'),
      '#size' => 20, '#maxlength' => 30 ,
      '#required' => TRUE,
      );
		  $form['form_edicion']['valor_consignacion']= array(
    	'#type' => 'textfield', 
    	'#title' => t('Valor Consignacion'),
      '#size' => 20, '#maxlength' => 30 ,
      '#required' => TRUE,
      );       
        
    }
  }
	
   
  return $form;
}

function cpnaa_vprof_tramite_oficina_callback($form, $form_state) {
  return $form['form_edicion'];
}
function cpnaa_vprof_tramite_oficina_incial_verificar($form, &$form_state) {
  $form_state['status']="datos_usuarios";
  $form_state['rebuild'] = TRUE;
}

function cpnaa_vprof_tramite_oficina_usuario_cancelar($form, &$form_state) {
  $form_state['status']="datos_usuarios";
  $form_state['rebuild'] = TRUE;
}

function cpnaa_vprof_tramite_oficina_usuario_continuar($form, &$form_state) {
  $form_state['status']="pago_oficina";
  $form_state['rebuild'] = TRUE;
}

function cpnaa_vprof_form_usuario(){
	$form = array();
	$form['nombre'] = array(
      '#type' => 'textfield',
      '#title' => t('Nombres: '),
      '#weight' => 4,
  );
  $form['apellido'] = array(
      '#type' => 'textfield',
      '#title' => t('Apellidos: '),
      '#weight' => 4,
  );
  $form['tipo_documento'] =array(
		'#type' => 'select',
		'#title' => t('Tipo de documento: '),
		'#options' => array(
			'Cedula' =>'Cedula',
			'Cedula de extrangeria' =>'Cedula de extrangeria',
			),
		'#weight' => 4,
	);
  $form['documento'] = array(
      '#type' => 'textfield',
      '#title' => t('Documento de identidad No: '),
      '#weight' => 4,
  );
  
  $deptos=cpnaa_tablas_get_select('departamento');
  $form['departamento'] = array(
      '#type' => 'select',
      '#title' => t('Departamento'),
      '#options' => $deptos,  
      '#weight' => 4,
  );
  $form['ciudad'] = array(
      '#type' => 'select',
      '#title' => t('Ciudad'), 
      '#prefix' => '<div id="form_user_ciudad">', '#suffix' => '</div>',
      '#weight' => 4,
  );
  return $form;
}