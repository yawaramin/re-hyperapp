/** Lightweight bindings to
    {{:https://github.com/jorgebucaran/hyperapp}Hyperapp}. Hyperapp has a
    very tiny API surface and already has a well-defined architecture, so
    we just follow that.

    JSX support is implemented in the [ReactDOMRe] and [ReasonReact]
    modules. See the former for more details. Note that both of these
    modules {i should not} be used directly; their purpose is to provide
    JSX support. */

/** Virtual DOM elements. I.e. the things that get rendered by views. */
type vdom;

/** Type of a custom component (i.e. a capitalized JSX element). This
    module type makes it possible to create higher-order components using
    OCaml functors, by declaring the functors to accept and return this
    type as input and output. Using this module type also enables the
    compiler to infer better types for state and actions, and avoids
    type errors caused by the value restriction on object types. I also
    strongly recommend enforcing this module type as it will guide you
    through the steps of creating the module--i.e. adding the required
    types and values. See also [StaticComponent] for an easy way to
    create stateless components.

    Strictly speaking, this exact type is not needed to support custom
    elements in JSX; at a minimum, the JSX transform just needs the last
    parameter ([children]), but usually you'll want to pass in state and
    actions objects, because the first two parameters are how Hyperapp
    threads state and actions through custom components.

    Note that you'll need to define the [state] and [actions] types as
    OCaml object types, but instantiate the [state] and [actions] values
    as BuckleScript objects. See
    [Yawaramin_ReHyperapp_Demo_Component_BookList.re] for more details.

    See also [ReasonReact] for more details on capitalized components,
    and [Yawaramin_ReHyperapp_Demo_Component_BookList.rei] for an example
    of how to enforce this module type on a file component. */
module type Component = {
  type state;
  type actions;
  type props;

  let state: Js.t(state);
  let actions: Js.t(actions);

  /** The parameter order in this definition is important–state and
      actions need to come first. */
  let make: (
    ~state: Js.t(state)=?,
    ~actions: Js.t(actions)=?,
    ~props: props,
    array(vdom),
  ) => vdom;
};

/** [empty()] allows creating empty JavaScript objects. These are useful
    for components that don't have any props or state and need JS objects
    that represent that. You can thus use `unit` as the [state] and
    [actions] types of components which don't have state or actions. */
[@bs.obj] external empty: unit => Js.t(unit) = "";

/** Helper module for creating static components. Include this module in
    your component module for a head start. Static components here mean
    components without state or actions. After including, you'll only
    need to define the type of [props] and the [make] function. */
module StaticComponent = {
  type state = unit;
  type actions = unit;

  let state = empty();
  let actions = empty();
};

type element = Dom.element;

/** A Hyperapp instance that can be mounted on the page. */
type t;

/** [array(vdoms)] allows injecting an array of VDOM nodes into a
    position where only a single one is expected. Hyperapp VDOM allows
    using an array of elements anywhere a child element is expected, so
    we don't really need fragments as such. */
external array: array(vdom) => vdom = "%identity";

external float: float => vdom = "%identity";
external int: int => vdom = "%identity";

/** [null] allows injecting 'nothing' into the VDOM. */
[@bs.val] external null: vdom = "";

/** [string(s)] allows injecting a string into the VDOM. */
external string: string => vdom = "%identity";

// The following two helpers are mostly not needed thanks to JSX support.

/** [h(tagName, attrs, children)] creates a [vdom] element with tag name
    [tagName], attributes [attrs], and child elements [children]. This is
    mostly useful for creating attributes that JSX doesn't support, e.g.
    [<div data-foo="bar">]. */
[@bs.module "hyperapp"]
external h: (string, Js.t({..}), array(vdom)) => vdom = "";

/** [h_(tagName, children)] creates a [vdom] element like above but with
    no attributes. */
[@bs.module "hyperapp"]
external h_: (string, [@bs.as {json|{}|json}] _, array(vdom)) => vdom =
  "h";

/** [make(~state, ~actions, ~view, element)] creates a Hyperapp instance.
    This is the main entry point to using this binding. Most of the type
    safety of the overall app comes from the way this function is typed:
    the view function must work with the state (model) and actions. */
[@bs.module "hyperapp"] external make: (
  ~state: Js.t({..}) as 'state,
  ~actions: Js.t({..}) as 'actions,
  ~view: (. 'state, 'actions) => vdom,
  Js.nullable(element),
) => t = "app";

/** Helper to get the DOM element that the [app] function needs to mount
    the app onto the page. */
[@bs.scope "document"] [@bs.val]
external getElementById: string => Js.nullable(element) = "";
