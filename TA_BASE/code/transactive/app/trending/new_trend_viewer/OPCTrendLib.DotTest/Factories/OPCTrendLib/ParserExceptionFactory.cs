using Dottest.Framework;
using Dottest.Framework.RecordState;
using NUnit.Framework;
using OPCTrendLib;
using System;

namespace DotTest.Factories.OPCTrendLib
{
    [TestFixture(), ObjectFactoryType()]
    public class ParserExceptionFactory
    {
        [ObjectFactoryMethod]
        [HashCode("/JM5hg", "/tQKCg")]
        public static ParserException CreateParserException01()
        {
            Error errorCode = Error.UnrecogniseChar;
            int pos = 0;
            ParserException parserException = new ParserException(errorCode, pos);
            return parserException;
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestCreateParserException01()
        {
            ParserException parserException = CreateParserException01();
            Assert.IsNotNull(parserException);
            #region Record State
            ValueRecorder recorder = new ValueRecorder();
            recorder.Record((string)parserException.HelpLink);
            recorder.Record((string)parserException.Message);
            recorder.Record((string)parserException.Source);
            recorder.Record((string)parserException.StackTrace);
            recorder.FinishRecording();
            #endregion
        }

        [ObjectFactoryMethod]
        [HashCode("/JM5hg", "+AgNxw")]
        public static ParserException CreateParserException02()
        {
            Error errorCode = Error.NoParenBefore;
            int pos = 1;
            ParserException parserException = new ParserException(errorCode, pos);
            return parserException;
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestCreateParserException02()
        {
            ParserException parserException = CreateParserException02();
            Assert.IsNotNull(parserException);
            #region Record State
            ValueRecorder recorder = new ValueRecorder();
            recorder.Record((string)parserException.HelpLink);
            recorder.Record((string)parserException.Message);
            recorder.Record((string)parserException.Source);
            recorder.Record((string)parserException.StackTrace);
            recorder.FinishRecording();
            #endregion
        }

        [ObjectFactoryMethod]
        [HashCode("/JM5hg", "+oe9+w")]
        public static ParserException CreateParserException03()
        {
            Error errorCode = Error.ErrorDoubleFormat;
            int pos = int.MinValue;
            ParserException parserException = new ParserException(errorCode, pos);
            return parserException;
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestCreateParserException03()
        {
            ParserException parserException = CreateParserException03();
            Assert.IsNotNull(parserException);
            #region Record State
            ValueRecorder recorder = new ValueRecorder();
            recorder.Record((string)parserException.HelpLink);
            recorder.Record((string)parserException.Message);
            recorder.Record((string)parserException.Source);
            recorder.Record((string)parserException.StackTrace);
            recorder.FinishRecording();
            #endregion
        }

    }
}