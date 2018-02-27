let actions = {"setQuery": [@bs] string => {query: string}};

let handleSearch(state) = [@bs] event =>
  switch (event##which, event##target##value) {
  | (_, "") => state
  | (13, query) => let action = actions##setQuery; [@bs] action(query)
  | _ => state
  };

let view(state) = Hyperapp.(
  h("nav", ~attrs={"class": "navbar is-dark", "role": "navigation"}, [|
    h("div", ~attrs={"class": "navbar-brand"}, [|
      h("a", ~attrs={"class": "navbar-item", "href": "#"}, [|
        h("img",
          ~attrs={
            "src": "http://via.placeholder.com/150x20",
            "alt": "Placeholder Logo",
            "width": "150px",
            "height": "20px"
          },
          [||])|])|]),

    h("div", ~attrs={"class": "navbar-menu is-active"}, [|
      h("div", ~attrs={"class": "navbar-start"}, [|
        h("div", ~attrs={"class": "navbar-item"}, [|
          string("Search Library:")|]),

        h("div", ~attrs={"class": "navbar-item"}, [|
          h("div", ~attrs={"class": "field"}, [|
            h("div", ~attrs={"class": "control is-expanded"}, [|
              h("input",
                ~attrs={
                  "class": "input is-normal",
                  "type": "text",
                  "onkeypress": handleSearch(state),
                  "placeholder": "Search Library"
                },
                [||])|])|])|])|])|])|]));
