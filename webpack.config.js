module.exports = {
    entry: './src/index.js',
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
    output: {
      path: __dirname + '/dist',
      publicPath: '/',
      filename: 'bundle.js'
    },
	devServer: {
        contentBase: './dist',
		host: "localhost",
		port: 9000,
		proxy: {
			"/oauth": {
				target: "http://localhost:56204",
				secure: false
			},

			"/api": {
				target: "http://localhost:56204",
				secure: false
			}
		}
	}
  };