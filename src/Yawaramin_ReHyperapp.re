/** (WIP) very minimalistic bindings to
    {{:https://github.com/jorgebucaran/hyperapp}Hyperapp}. Hyperapp has a
    very tiny API surface and already has a well-defined architecture, so
    we just follow that.

    JSX support is implemented in the [ReactDOMRe] and [ReasonReact]
    modules. See the former for more details. Note that both of these
    modules {i should not} be used directly; their purpose is to provide
    JSX support.

    For capitalized elements in JSX (i.e. what React would call custom
    components), the requirement is that the module which will be used as
    a custom component implement a Hyperapp view function {i but} give it
    the following shape:
    [let make(~prop1, ..., ~propN, children) = ...;]. In other words some
    number of named props and a final parameter for the (possible)
    children. Usually the props will be [~state] and [~actions] because
    that's what Hyperapp views expect. */

/** Virtual DOM elements. I.e. the things that get rendered by views. */
type vdom;
type t;
type element = Dom.element;

external string: string => vdom = "%identity";
external int: int => vdom = "%identity";
external float: float => vdom = "%identity";

/** [h(tagName, attrs, children)] creates a [vdom] element with tag name
    [tagName], attributes [attrs], and child elements [children]. This is
    mostly useful for creating attributes that JSX doesn't support, e.g.
    [<div data-foo="bar">]. */
[@bs.module "hyperapp"]
external h: (string, Js.t({..}), array(vdom)) => vdom = "";

/** [h_(tagName, children)] creates a [vdom] element like above but with
    no attributes. */
[@bs.module "hyperapp"]
external h_: (string, [@bs.as {json|{}|json}] _, array(vdom)) => vdom = "h";

/** [make(~state, ~actions, ~view, element)] creates a Hyperapp instance.
    Most of the type safety of the overall app comes from the way this
    function is typed: the view function must work with the state (model)
    and actions. */
[@bs.module "hyperapp"] external make: (
  ~state: Js.t({..}) as 'state,
  ~actions: Js.t({..}) as 'actions,
  ~view: (. 'state, 'actions) => vdom,
  element,
) => t = "app";

/** Helper to get the DOM element that the [app] function needs to mount
    the app onto the page. */
[@bs.scope "document"] [@bs.val]
external getElementById: string => Js.nullable(element) = "";
