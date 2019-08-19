# TestWebpack2

Sources:
- https://github.com/rwieruch/advanced-react-webpack-babel-setup
- https://www.robinwieruch.de/webpack-advanced-setup-tutorial/

On commence par créer un projet sur github, après quoi on clone le repo pour créer le dossier du projet et avoir un fichier de config de git déjà prêt
 
npm init (Version simplidiée npm init -y)
mkdir src
cd src
touch index.js (fsutil file createnew index.js 0)

Dans le fichier package.json, ajouter les scripts suivants:
	"start": "webpack-dev-server --config ./webpack.config.js --mode development",
    "build": "webpack --config ./webpack.config.js --mode production",
    "lint": "eslint . || ECHO.",
    "lint-fix": "eslint . --fix || ECHO.",
    "webpack": "webpack --bail",
    "freshtall": "npm cache clean --force && rm -rf node_modules && rm -f package-lock.json && npm install"
	
mkdir dist
cd dist
touch index.html (fsutil file createnew index.html 0)
Y ajouter:
	<!DOCTYPE html>
	<html>
	  <head>
		<title>Hello Webpack</title>
	  </head>
	  <body>
		<div>
		  <h1>Hello Webpack</h1>
		</div>
		<script src="./bundle.js"></script>
	  </body>
	</html>

npm install --save-dev webpack webpack-dev-server webpack-cli

Ajouter un fichier .gitignore à la racine avec dedans node_modules

Création fichier webpack.config.js à la racine avec dedans:
	module.exports = {
	  // 1
	  entry: './src/index.js',
	  // 2
	  output: {
		path: __dirname + '/dist',
		publicPath: '/',
		filename: 'bundle.js'
	  },
	  // 3
	  devServer: {
		contentBase: './dist'
	  }
	};

-- Ajout de babel --
npm install --save-dev @babel/core @babel/preset-env
npm install --save-dev babel-loader
Ajout ce passage dans le fichier webpack.config.js:
	 module: {
    rules: [
      {
        test: /\.(js)$/,
        exclude: /node_modules/,
        use: ['babel-loader']
      }
    ]
  },
  resolve: {
    extensions: ['*', '.js']
  },
  
 Créer fichier .babelrc avec à l'intérieur:
	{
	  "presets": [
		"@babel/preset-env"
	  ]
	}

--> Pour debug --> npm start
--> Pour la prod --> npm run build

Pour tester le build résultant, on install un serveur web global et on le run
	npm install -g http-server
	http-server dist (On peut changer le port en rajoutant -p 9000 par exemple)
(Actuellement une erreur ERR_INVALID_REDIRECT apparait, il faut soit downgrade http-server en 0.9 ou juste rajouter index.html)

Pour faire un clean du dossier dist avant chaque build, on rajoute:
npm install --save-dev html-webpack-plugin
Dans le fichier webpack.config.js, on rajoute:
	const HtmlWebpackPlugin = require('html-webpack-plugin')
	
	plugins: [
		new HtmlWebpackPlugin({
		  title: 'Hello Webpack bundled JavaScript Project',
		  template: './src/index.html'
		})
	  ],
Du coup il faut bouger le template HTML vers le dossier src avec dedans:
	<!DOCTYPE html>
	<html>
	  <head>
		<title><%= htmlWebpackPlugin.options.title %></title>
	  </head>
	  <body>
		<div>
		  <h1><%= htmlWebpackPlugin.options.title %></h1>

		</div>
	  </body>
	</html>
On a plus besoin de spécifier le nom de bundle.js dans le fichier html

Pour bien tout nettoyer avant on doit rajouter 
npm install --save-dev clean-webpack-plugin
 et ds le fichier webpack.config.js
	const { CleanWebpackPlugin } = require('clean-webpack-plugin');
	
	plugins: [
    new CleanWebpackPlugin(),
	
On peut rajouter dist dans le .gitignore

On rajoute la notion de map des fichiers js pour pouvoir avoir des logs utilisables même après bundle.

  devtool: 'source-map',
  
On divise la config de webpack en plusieurs fichiers qui seront fusionnés avec:
npm install --save-dev webpack-merge
Ds webpack.config.js, on change:
	"start": "webpack-dev-server --config build-utils/webpack.config.js --env.env=dev",
    "build": "webpack --config build-utils/webpack.config.js --env.env=prod",
	
On crée les fichiers
- build-utils/
-- webpack.common.js
-- webpack.config.js
-- webpack.dev.js
-- webpack.prod.js

Pour utiliser des variables statiques par environnement, on install:
npm install dotenv-webpack --save-dev
Et on crée des fichiers .env.development & .env.production
On rajoute ces fichiers dans le .gitignore pour ne pas les envoyer sur Git car ces fichiers sont destinés à contenir des données sensibles telles que des adresses IP ou des URL.
