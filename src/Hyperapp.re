type vdom;
type app;
type element;

external string: string => vdom = "%identity";
external int: int => vdom = "%identity";

[@bs.module "hyperapp"]
external h: (string, ~attrs: Js.t({..})=?, array(vdom)) => vdom = "";

[@bs.module "hyperapp"] external app: (
  ~state: Js.t({..}) as 'state,
  ~actions: Js.t({..}) as 'actions,
  ~view: [@bs] ('state, 'actions) => vdom,
  element) =>
  app =
  "";

[@bs.scope "document"] [@bs.val]
external getElementById: string => Js.nullable(element) = "";
