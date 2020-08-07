# OpenVPN Configuration Files Converter

This is a simple command line tool for converting files from OVPN [1] format to JSON [2].

This tool also supports basic validation of source OVPN files for unknown options, number of arguments and their types.

**The tool is under development and has the alpha release status.**

[1]: https://openvpn.net/community-resources/reference-manual-for-openvpn-2-4/
[2]: wikipedia.org/wiki/JSON

## Usage

Usage syntax:
```shell
ovpn-convert [options] <input-file>
```

*   `[options]` is a one or more additional optional options that are described in the "[Options](#options)" section.
*   `<input-file>` is the path to the source OVPN file to be converted. Input OVPN file path should not be specified if selected the input from standard input (stdin) using additional option `--stdin` (see the "[Options](#options)" section).

### Options

#### `-h`, `--help`

Show help and usage text.

#### `-s`, `--stdin`

Use standard input (stdin) for input data. When this option is specified, no `<input-file>` is required.

#### `-p`, `--pretty`

Use formatted JSON output with tab-indentation.

#### `-i`, `--include-status`

By default status information is dumped separately to stderr stream. This option allows to include parsing status information into main JSON output.

#### `-l <path>`, `--locale-path <path>`

Path to directory with locale (`mo`) files

#### `-L <language>`, `--language <language>`

Manually specify language. By default language is determined from `LANG` environment variable.

## JSON Output Format

JSON output has the following format:
```
{
	"inlines": {
		"<inline-option-1-name>": {
			"type": "<inline-option-1-data-type>",
			"data": [
				<inline-option-1-occurence-1-data>,
				...
				<inline-option-1-occurence-M-data>
			]
		},

		...

		"<inline-option-N-name>": {
			...
		},
	},
	"options": {
		"<option-1-name>": [
			{
				"args": [
					<option-1-occurence-1-arg-1-value>,
					...
					<option-1-occurence-K-arn-L-value>
				]
			},

			...

			{
				"args": [
					<option-1-occurence-2-arg-1-value>,
					...
					<option-1-occurence-P-arg-R-value>
				]
			}
		],

		...

		"<option-S-name>": [
			...
		],
	}
}
```

where:

*   `<inline-option-X-name>`: Inline option X name.
*   `<inline-option-X-data-type>`: Inline data type for option X. Can be `plain` or `options`. If inline data type if `plain` then data (`<inline-option-X-occurence-Y-data>`) is string with plain option data. If inline data is `options` then data is JSON object with options data such as main JSON `options` object.
*   `<inline-option-X-occurence-Y-data>`: Option data for each option occurence.
*   `<option-X-name>`: Option X name.
*   `<option-X-occurence-Y-arg-Z-value>`: Arguments for each occurence of option X.

Validation warnings and errors will be outputed to stderr stream in the following format:
```
{
	"errors": <count-of-errors>,
	"warnings": <count-of-warnings>,
	"messages": [
		{
			"type": "<message-1-type>",
			"message": "<messsage-1-text>",
			"line": <message-1-line>
		},

		...

		{
			"type": "<message-N-type>",
			"message": "<messsage-N-text>",
			"line": <message-N-line>
		}
	]
}
```

where:

*   `<count-of-errors>`: Total count of founded errors.
*   `<count-of-warnings>`: Total count of founded warnings.
*   `<message-N-type>`: Type of message (`error` or `warning`).
*   `<message-N-text>`: Message text.
*   `<message-N-line>`: The number of the line in the source OVPN file to which the message refers. The parameter may not exist. In this case, the message refers to the file as a whole.

The total count `N` of messages corresponds to the sum of errors and warnings.

If `--include-status` option is specified (see "[Options](#options)" section), then JSON object with validation error and warnings information will be inserted into main JSON object with `status` name.

### Example

Source OVPN file:
```
client
dev tun3
proto tcp
remote 11.222.111.22 80
remote vpn.example.com 80
resolv-retry infinite
nobind
persist-key
persist-tun
auth-user-pass
comp-lzo
verb 3
cipher AES-128-CBC
fast-io
pull
route-delay 2
redirect-gateway
<ca>
-----BEGIN CERTIFICATE-----
CA PLAIN DATA
-----END CERTIFICATE-----
</ca>
<cert>
-----BEGIN CERTIFICATE-----
CERT PLAIN DATA
-----END CERTIFICATE-----
</cert>
<key>
-----BEGIN RSA PRIVATE KEY-----
KEY PLAIN DATA
-----END RSA PRIVATE KEY-----
</key>
```

JSON output for this example will be following:
```json
{"inlines":{"ca":{"type":"plain","data":["-----BEGIN CERTIFICATE-----\r\nCA PLAIN DATA\r\n-----END CERTIFICATE-----\r\n"]},"cert":{"type":"plain","data":["-----BEGIN CERTIFICATE-----\r\nCERT PLAIN DATA\r\n-----END CERTIFICATE-----\r\n"]},"key":{"type":"plain","data":["-----BEGIN RSA PRIVATE KEY-----\r\nKEY PLAIN DATA\r\n-----END RSA PRIVATE KEY-----\r\n"]}},"options":{"client":[{"args":[]}],"dev":[{"args":["tun3"]}],"proto":[{"args":["tcp"]}],"remote":[{"args":["11.222.111.22","80"]},{"args":["vpn.example.com","80"]}],"resolv-retry":[{"args":["infinite"]}],"nobind":[{"args":[]}],"persist-key":[{"args":[]}],"persist-tun":[{"args":[]}],"auth-user-pass":[{"args":[]}],"comp-lzo":[{"args":[]}],"verb":[{"args":["3"]}],"cipher":[{"args":["AES-128-CBC"]}],"fast-io":[{"args":[]}],"pull":[{"args":[]}],"route-delay":[{"args":["2"]}],"redirect-gateway":[{"args":[]}]}}
```

JSON formatted output (`-p` option is specified) for this example will be following:
```json
{
	"inlines":{
		"ca":{
			"type":"plain",
			"data":[
				"-----BEGIN CERTIFICATE-----\r\nCA PLAIN DATA\r\n-----END CERTIFICATE-----\r\n"
			]
		},
		"cert":{
			"type":"plain",
			"data":[
				"-----BEGIN CERTIFICATE-----\r\nCERT PLAIN DATA\r\n-----END CERTIFICATE-----\r\n"
			]
		},
		"key":{
			"type":"plain",
			"data":[
				"-----BEGIN RSA PRIVATE KEY-----\r\nKEY PLAIN DATA\r\n-----END RSA PRIVATE KEY-----\r\n"
			]
		}
	},
	"options":{
		"client":[
			{
				"args":[
				]
			}
		],
		"dev":[
			{
				"args":[
					"tun3"
				]
			}
		],
		"proto":[
			{
				"args":[
					"tcp"
				]
			}
		],
		"remote":[
			{
				"args":[
					"11.222.111.22",
					"80"
				]
			},
			{
				"args":[
					"vpn.example.com",
					"80"
				]
			}
		],
		"resolv-retry":[
			{
				"args":[
					"infinite"
				]
			}
		],
		"nobind":[
			{
				"args":[
				]
			}
		],
		"persist-key":[
			{
				"args":[
				]
			}
		],
		"persist-tun":[
			{
				"args":[
				]
			}
		],
		"auth-user-pass":[
			{
				"args":[
				]
			}
		],
		"comp-lzo":[
			{
				"args":[
				]
			}
		],
		"verb":[
			{
				"args":[
					"3"
				]
			}
		],
		"cipher":[
			{
				"args":[
					"AES-128-CBC"
				]
			}
		],
		"fast-io":[
			{
				"args":[
				]
			}
		],
		"pull":[
			{
				"args":[
				]
			}
		],
		"route-delay":[
			{
				"args":[
					"2"
				]
			}
		],
		"redirect-gateway":[
			{
				"args":[
				]
			}
		]
	}
}
```

Validation errors and warnings for this example will be following:
```json
{
	"errors":0,
	"warnings":1,
	"messages":[
		{
			"type":"warning",
			"message":"Option 'comp-lzo' is deprecated and can be removed in future OpenVPN versions",
			"line":11
		}
	]
}
```

## License

This work is free. You can redistribute it and/or modify it under the terms of the Do What The Fuck You Want To Public License, Version 2, as published by Sam Hocevar. See <http://www.wtfpl.net/> for more details.

## Authors

*   Anton Kikin <mailto:a.kikin@tano-systems.com>
