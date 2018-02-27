type state = {. "query": string};

let state = {"query": ""};
let actions = {"setQuery": [@bs] string => {query: string}};

let handleSearch(state) = [@bs] event =>
  switch (event##which, event##target##value) {
  | (_, "") => state
  | (13, query) => let action = actions##setQuery; [@bs] action(query)
  | _ => state
  };

let view(state) = Hyperapp.(
  h("nav", {"class": "navbar is-dark", "role": "navigation"}, [|
    h("div", {"class": "navbar-brand"}, [|
      h("a", {"class": "navbar-item", "href": "#"}, [|
        h("img",
          {
            "src": "http://via.placeholder.com/150x20",
            "alt": "Placeholder Logo",
            "width": "150px",
            "height": "20px"
          },
          [||])|])|]),

    h("div", {"class": "navbar-menu is-active"}, [|
      h("div", {"class": "navbar-start"}, [|
        h("div", {"class": "navbar-item"}, [|
          string("Search Library:")|]),

        h("div", {"class": "navbar-item"}, [|
          h("div", {"class": "field"}, [|
            h("div", {"class": "control is-expanded"}, [|
              h("input",
                {
                  "class": "input is-normal",
                  "type": "text",
                  "onkeypress": handleSearch(state),
                  "placeholder": "Search Library"
                },
                [||])|])|])|])|])|])|]));
