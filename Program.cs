
﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Text;

namespace CF
{
    using IO;
    class Program
    {
        static void Main(string[] args)
        {
            StreamReader Reader = new StreamReader(Console.OpenStandardInput(1024 * 10), Encoding.ASCII, false, 1024 * 10); StreamWriter Writer = new StreamWriter(Console.OpenStandardOutput(1024 * 10), Encoding.ASCII, 1024 * 10);
            Read Cin = new Read(Reader);
            int n = Cin.NextInt();
            Writer.Flush();
        }
    }

}
namespace IO
{
    public class Read
    {
        static StreamReader reader;

        public Read(StreamReader ExternalReader)
        {
            reader = ExternalReader;
        }

        /// <summary>
        /// Reads a string token from the console
        /// skipping any leading and trailing whitespace.
        /// </summary>
        public string NextToken()
        {
            StringBuilder tokenChars = new StringBuilder();
            bool tokenFinished = false;
            bool skipWhiteSpaceMode = true;
            while (!tokenFinished)
            {
                int nextChar = reader.Read();
                if (nextChar == -1)
                {
                    // End of stream reached
                    tokenFinished = true;
                }
                else
                {
                    char ch = (char)nextChar;
                    if (char.IsWhiteSpace(ch))
                    {
                        // Whitespace reached (' ', '\r', '\n', '\t') -->
                        // skip it if it is a leading whitespace
                        // or stop reading anymore if it is trailing
                        if (!skipWhiteSpaceMode)
                        {
                            tokenFinished = true;
                            if (ch == '\r' && (Environment.NewLine == "\r\n"))
                            {
                                // Reached '\r' in Windows --> skip the next '\n'
//                                Console.Read();
                            }
                        }
                    }
                    else
                    {
                        // Character reached --> append it to the output
                        skipWhiteSpaceMode = false;
                        tokenChars.Append(ch);
                    }
                }
            }

            string token = tokenChars.ToString();
            return token;
        }

        public int NextInt()
        {
            return int.Parse(NextToken());
        }
        public double NextDouble()
        {
            return double.Parse(NextToken());
        }
    }
}
