// Code generated by easyjson for marshaling/unmarshaling. DO NOT EDIT.

package benchmarks

import (
	json "encoding/json"
	easyjson "github.com/mailru/easyjson"
	jlexer "github.com/mailru/easyjson/jlexer"
	jwriter "github.com/mailru/easyjson/jwriter"
)

// suppress unused package warning
var (
	_ *json.RawMessage
	_ *jlexer.Lexer
	_ *jwriter.Writer
	_ easyjson.Marshaler
)

func easyjsonA80d3b19DecodeGitItvRestrImItvBackendReindexerBenchmarks(in *jlexer.Lexer, out *Item) {
	isTopLevel := in.IsStart()
	if in.IsNull() {
		if isTopLevel {
			in.Consumed()
		}
		in.Skip()
		return
	}
	in.Delim('{')
	for !in.IsDelim('}') {
		key := in.UnsafeString()
		in.WantColon()
		if in.IsNull() {
			in.Skip()
			in.WantComma()
			continue
		}
		switch key {
		case "id":
			out.ID = int64(in.Int64())
		case "name":
			out.Name = string(in.String())
		case "year":
			out.Year = int(in.Int())
		default:
			in.SkipRecursive()
		}
		in.WantComma()
	}
	in.Delim('}')
	if isTopLevel {
		in.Consumed()
	}
}
func easyjsonA80d3b19EncodeGitItvRestrImItvBackendReindexerBenchmarks(out *jwriter.Writer, in Item) {
	out.RawByte('{')
	first := true
	_ = first
	if !first {
		out.RawByte(',')
	}
	first = false
	out.RawString("\"id\":")
	out.Int64(int64(in.ID))
	if !first {
		out.RawByte(',')
	}
	first = false
	out.RawString("\"name\":")
	out.String(string(in.Name))
	if !first {
		out.RawByte(',')
	}
	first = false
	out.RawString("\"year\":")
	out.Int(int(in.Year))
	out.RawByte('}')
}

// MarshalJSON supports json.Marshaler interface
func (v Item) MarshalJSON() ([]byte, error) {
	w := jwriter.Writer{}
	easyjsonA80d3b19EncodeGitItvRestrImItvBackendReindexerBenchmarks(&w, v)
	return w.Buffer.BuildBytes(), w.Error
}

// MarshalEasyJSON supports easyjson.Marshaler interface
func (v Item) MarshalEasyJSON(w *jwriter.Writer) {
	easyjsonA80d3b19EncodeGitItvRestrImItvBackendReindexerBenchmarks(w, v)
}

// UnmarshalJSON supports json.Unmarshaler interface
func (v *Item) UnmarshalJSON(data []byte) error {
	r := jlexer.Lexer{Data: data}
	easyjsonA80d3b19DecodeGitItvRestrImItvBackendReindexerBenchmarks(&r, v)
	return r.Error()
}

// UnmarshalEasyJSON supports easyjson.Unmarshaler interface
func (v *Item) UnmarshalEasyJSON(l *jlexer.Lexer) {
	easyjsonA80d3b19DecodeGitItvRestrImItvBackendReindexerBenchmarks(l, v)
}