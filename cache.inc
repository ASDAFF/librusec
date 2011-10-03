<?php

// APC ���. 
// + �������� ������� ������ ������� ������� 
// - �������� ������ ����������, �� �������� � ������ ��������, 
// -+ ���������� ��� ������������ apache

// ����� �� APC. 
// ID ���������� ������������� �� ����� ���������� ������� + $id �����������
// � ����������� ��� ���������� ������ setapc
// ���������� ��������: if ($r = getapc(func_get_args())) return $r; else return setpac(AnySlowFunction());
function getapc($id='') {
  Global $apc_cid;
  $f = debug_backtrace();
  $f = $f[1]['function'];
  if (!is_scalar($id)) $id = md5(serialize($id));
  $apc_cid[$f] = $f.$id;
  return apc_fetch($apc_cid[$f]);
}

// �������� $val � APC �� $tm ������ (0 - ������� �����, �� ������ apache). 
// ID ����������� � ����������� ������ getapc, ������� ������ ��� ����� setapc.
// ���������� $val ��� ��������� ��������� ����� ������� return setapc(...); ������ ��� $r = ...; setapc($r); return $r;
function setapc($val, $tm = 583) {
  Global $apc_cid;
  $f = debug_backtrace();
  $f = $f[1]['function'];
  apc_store($apc_cid[$f], $val, $tm);
  return $val;
}
