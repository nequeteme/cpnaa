<?php

/*
 * Metodo para retornar los datos para un select
 *
 * @param $alias_tabla: tabla para hacer el select
 * @param $foren_key: id de la llave foranea para traer el dato encadenado, ejemplo ciudad de un departamento
 * @return array con los datos para el select
 */
function cpnaa_tablas_get_select($alias_tabla='departamento', $foren_key='') {
	global $CPNAA_tablas_names;
	$query = db_select($CPNAA_tablas_names[$alias_tabla]['table'] , 'd');
  if(($foren_key!='') && (!empty($CPNAA_tablas_names[$alias_tabla]['fk']) )){
  	$query->condition('d.'.$CPNAA_tablas_names[$alias_tabla]['fk'], $foren_key, '=')
      ->fields('d', array('id', $CPNAA_tablas_names[$alias_tabla]['info']));
  }
  else {
  	$query->fields('d', array('id', $CPNAA_tablas_names[$alias_tabla]['info']));
  }
	$result = $query->execute();
	$data=false;
	$data['0']='Seleccione uno';
	foreach ($result as $row) {
		$data[$row->id]=$row->$CPNAA_tablas_names[$alias_tabla]['info'];							
	}
	return $data;	
}


/*
 * Metodo para retornar las tablas para un select
 *
 * @return array con los datos para el select
 */
function cpnaa_tablas_get_tablas_select(){
	$data=false;
	global $CPNAA_tablas_names;
	foreach ($CPNAA_tablas_names as $key => $value) {
		$data[$key]=$key;
	}
	return $data;
}