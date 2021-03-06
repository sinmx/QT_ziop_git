using Dottest.Framework;
using Dottest.Framework.RecordState;
using NUnit.Framework;
using System;
using System.Windows.Forms;
using TrendViewer.View;

namespace TrendViewer.DotTest.Factories.View
{
    [TestFixture(), ObjectFactoryType()]
    public class HistDataPointListFactory
    {
        ///<summary>A caller is responsible for disposing the result</summary>
        [ObjectFactoryMethod]
        [HashCode("+kMgqw", "+WkqrA")]
        public static HistDataPointList CreateHistDataPointList01()
        {
            HistDataPointList histDataPointList = new HistDataPointList();
            return histDataPointList;
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestCreateHistDataPointList01()
        {
            using (HistDataPointList histDataPointList = CreateHistDataPointList01())
            {
                Assert.IsNotNull(histDataPointList);
                #region Record State
                ValueRecorder recorder = new ValueRecorder();
                recorder.Record((string)histDataPointList.AccessibleDefaultActionDescription);
                recorder.Record((string)histDataPointList.AccessibleDescription);
                recorder.Record((string)histDataPointList.AccessibleName);
                recorder.Record((AccessibleRole)histDataPointList.AccessibleRole);
                recorder.Record((bool)histDataPointList.AllowDrop);
                recorder.Record((bool)histDataPointList.AllowTransparency);
                recorder.Record((AnchorStyles)histDataPointList.Anchor);
                recorder.Record((AutoScaleMode)histDataPointList.AutoScaleMode);
                recorder.Record((bool)histDataPointList.AutoScroll);
                recorder.Record((bool)histDataPointList.AutoSize);
                recorder.Record((AutoSizeMode)histDataPointList.AutoSizeMode);
                recorder.Record((AutoValidate)histDataPointList.AutoValidate);
                recorder.Record((ImageLayout)histDataPointList.BackgroundImageLayout);
                recorder.Record((int)histDataPointList.Bottom);
                recorder.Record((bool)histDataPointList.CanFocus);
                recorder.Record((bool)histDataPointList.CanSelect);
                recorder.Record((bool)histDataPointList.Capture);
                recorder.Record((bool)histDataPointList.CausesValidation);
                recorder.Record((string)histDataPointList.CompanyName);
                recorder.Record((bool)histDataPointList.ContainsFocus);
                recorder.Record((bool)histDataPointList.ControlBox);
                recorder.Record((bool)histDataPointList.Created);
                recorder.Record((DialogResult)histDataPointList.DialogResult);
                recorder.Record((bool)histDataPointList.Disposing);
                recorder.Record((DockStyle)histDataPointList.Dock);
                recorder.Record((bool)histDataPointList.Enabled);
                recorder.Record((bool)histDataPointList.Focused);
                recorder.Record((FormBorderStyle)histDataPointList.FormBorderStyle);
                recorder.Record((bool)histDataPointList.HasChildren);
                recorder.Record((int)histDataPointList.Height);
                recorder.Record((bool)histDataPointList.HelpButton);
                recorder.Record((ImeMode)histDataPointList.ImeMode);
                recorder.Record((bool)histDataPointList.InvokeRequired);
                recorder.Record((bool)histDataPointList.IsAccessible);
                recorder.Record((bool)histDataPointList.IsDisposed);
                recorder.Record((bool)histDataPointList.IsHandleCreated);
                recorder.Record((bool)histDataPointList.IsMdiChild);
                recorder.Record((bool)histDataPointList.IsMdiContainer);
                recorder.Record((bool)histDataPointList.IsMirrored);
                recorder.Record((bool)histDataPointList.IsRestrictedWindow);
                recorder.Record((bool)histDataPointList.KeyPreview);
                recorder.Record((int)histDataPointList.Left);
                recorder.Record((bool)histDataPointList.MaximizeBox);
                recorder.Record((bool)histDataPointList.MinimizeBox);
                recorder.Record((bool)histDataPointList.Modal);
                recorder.Record((string)histDataPointList.Name);
                recorder.Record((double)histDataPointList.Opacity);
                recorder.Record((string)histDataPointList.ProductName);
                recorder.Record((string)histDataPointList.ProductVersion);
                recorder.Record((bool)histDataPointList.RecreatingHandle);
                recorder.Record((int)histDataPointList.Right);
                recorder.Record((RightToLeft)histDataPointList.RightToLeft);
                recorder.Record((bool)histDataPointList.RightToLeftLayout);
                recorder.Record((bool)histDataPointList.ShowIcon);
                recorder.Record((bool)histDataPointList.ShowInTaskbar);
                recorder.Record((SizeGripStyle)histDataPointList.SizeGripStyle);
                recorder.Record((FormStartPosition)histDataPointList.StartPosition);
                recorder.Record((bool)ReflectionAccessor.Wrap(histDataPointList).GetProperty("System.Windows.Forms.Layout.IArrangedElement.ParticipatesInLayout"));
                recorder.Record((int)histDataPointList.TabIndex);
                recorder.Record((bool)histDataPointList.TabStop);
                recorder.Record((string)histDataPointList.Text);
                recorder.Record((int)histDataPointList.Top);
                recorder.Record((bool)histDataPointList.TopLevel);
                recorder.Record((bool)histDataPointList.TopMost);
                recorder.Record((bool)histDataPointList.UseWaitCursor);
                recorder.Record((string)histDataPointList.ViewID);
                recorder.Record((string)histDataPointList.ViewType);
                recorder.Record((bool)histDataPointList.Visible);
                recorder.Record((int)histDataPointList.Width);
                recorder.Record((FormWindowState)histDataPointList.WindowState);
                recorder.FinishRecording();
                #endregion
                #region Assertions
                Assert.IsNull((string)histDataPointList.AccessibleDefaultActionDescription);
                Assert.IsFalse((bool)histDataPointList.AllowDrop);
                Assert.AreEqual(global::System.Windows.Forms.AutoScaleMode.Font, (AutoScaleMode)histDataPointList.AutoScaleMode);
                Assert.AreEqual(global::System.Windows.Forms.AutoValidate.EnablePreventFocusChange, (AutoValidate)histDataPointList.AutoValidate);
                Assert.IsFalse((bool)histDataPointList.CanFocus);
                Assert.AreEqual("ST Electronics Ltd", (string)histDataPointList.CompanyName);
                Assert.IsFalse((bool)histDataPointList.Created);
                Assert.IsTrue((bool)histDataPointList.Enabled);
                Assert.IsTrue((bool)histDataPointList.HasChildren);
                Assert.IsFalse((bool)histDataPointList.InvokeRequired);
                Assert.IsFalse((bool)histDataPointList.IsHandleCreated);
                Assert.IsFalse((bool)histDataPointList.IsRestrictedWindow);
                Assert.IsFalse((bool)histDataPointList.MaximizeBox);
                Assert.AreEqual(1.0, (double)histDataPointList.Opacity, 1E-7);
                Assert.IsFalse((bool)histDataPointList.RecreatingHandle);
                Assert.IsTrue((bool)histDataPointList.ShowIcon);
                Assert.AreEqual(global::System.Windows.Forms.FormStartPosition.CenterScreen, (FormStartPosition)histDataPointList.StartPosition);
                Assert.AreEqual("Historical Datapoint Viewer", (string)histDataPointList.Text);
                Assert.IsFalse((bool)histDataPointList.TopMost);
                Assert.IsFalse((bool)histDataPointList.Visible);
                #endregion
            }
        }

    }
}
