using Dottest.Framework;
using Dottest.Framework.RecordState;
using NUnit.Framework;
using System;
using System.Windows.Forms;
using TrendViewer.View;

namespace TrendViewer.DotTest.Factories.View
{
    [TestFixture(), ObjectFactoryType()]
    public class MarkerListFactory
    {
        ///<summary>A caller is responsible for disposing the result</summary>
        [ObjectFactoryMethod]
        [HashCode("/egCQw", "+oWDqg")]
        public static MarkerList CreateMarkerList01()
        {
            MarkerList markerList = new MarkerList();
            return markerList;
        }

        [TestCaseUnverified("Test case not verified")]
        [TestCaseAutogenerated]
        [TestAuthor("user")]
        [Test]
        public void TestCreateMarkerList01()
        {
            using (MarkerList markerList = CreateMarkerList01())
            {
                Assert.IsNotNull(markerList);
                #region Record State
                ValueRecorder recorder = new ValueRecorder();
                recorder.Record((string)markerList.AccessibleDefaultActionDescription);
                recorder.Record((string)markerList.AccessibleDescription);
                recorder.Record((string)markerList.AccessibleName);
                recorder.Record((AccessibleRole)markerList.AccessibleRole);
                recorder.Record((bool)markerList.AllowDrop);
                recorder.Record((bool)markerList.AllowTransparency);
                recorder.Record((AnchorStyles)markerList.Anchor);
                recorder.Record((AutoScaleMode)markerList.AutoScaleMode);
                recorder.Record((bool)markerList.AutoScroll);
                recorder.Record((bool)markerList.AutoSize);
                recorder.Record((AutoSizeMode)markerList.AutoSizeMode);
                recorder.Record((AutoValidate)markerList.AutoValidate);
                recorder.Record((ImageLayout)markerList.BackgroundImageLayout);
                recorder.Record((int)markerList.Bottom);
                recorder.Record((bool)markerList.CanFocus);
                recorder.Record((bool)markerList.CanSelect);
                recorder.Record((bool)markerList.Capture);
                recorder.Record((bool)markerList.CausesValidation);
                recorder.Record((string)markerList.CompanyName);
                recorder.Record((bool)markerList.ContainsFocus);
                recorder.Record((bool)markerList.ControlBox);
                recorder.Record((bool)markerList.Created);
                recorder.Record((DialogResult)markerList.DialogResult);
                recorder.Record((bool)markerList.Disposing);
                recorder.Record((DockStyle)markerList.Dock);
                recorder.Record((bool)markerList.Enabled);
                recorder.Record((bool)markerList.Focused);
                recorder.Record((FormBorderStyle)markerList.FormBorderStyle);
                recorder.Record((bool)markerList.HasChildren);
                recorder.Record((int)markerList.Height);
                recorder.Record((bool)markerList.HelpButton);
                recorder.Record((ImeMode)markerList.ImeMode);
                recorder.Record((bool)markerList.InvokeRequired);
                recorder.Record((bool)markerList.IsAccessible);
                recorder.Record((bool)markerList.IsDisposed);
                recorder.Record((bool)markerList.IsHandleCreated);
                recorder.Record((bool)markerList.IsMdiChild);
                recorder.Record((bool)markerList.IsMdiContainer);
                recorder.Record((bool)markerList.IsMirrored);
                recorder.Record((bool)markerList.IsRestrictedWindow);
                recorder.Record((bool)markerList.KeyPreview);
                recorder.Record((int)markerList.Left);
                recorder.Record((bool)markerList.MaximizeBox);
                recorder.Record((bool)markerList.MinimizeBox);
                recorder.Record((bool)markerList.Modal);
                recorder.Record((string)markerList.Name);
                recorder.Record((double)markerList.Opacity);
                recorder.Record((string)markerList.ProductName);
                recorder.Record((string)markerList.ProductVersion);
                recorder.Record((bool)markerList.RecreatingHandle);
                recorder.Record((int)markerList.Right);
                recorder.Record((RightToLeft)markerList.RightToLeft);
                recorder.Record((bool)markerList.RightToLeftLayout);
                recorder.Record((bool)markerList.ShowIcon);
                recorder.Record((bool)markerList.ShowInTaskbar);
                recorder.Record((SizeGripStyle)markerList.SizeGripStyle);
                recorder.Record((FormStartPosition)markerList.StartPosition);
                recorder.Record((bool)ReflectionAccessor.Wrap(markerList).GetProperty("System.Windows.Forms.Layout.IArrangedElement.ParticipatesInLayout"));
                recorder.Record((int)markerList.TabIndex);
                recorder.Record((bool)markerList.TabStop);
                recorder.Record((string)markerList.Text);
                recorder.Record((int)markerList.Top);
                recorder.Record((bool)markerList.TopLevel);
                recorder.Record((bool)markerList.TopMost);
                recorder.Record((bool)markerList.UseWaitCursor);
                recorder.Record((string)markerList.ViewID);
                recorder.Record((string)markerList.ViewType);
                recorder.Record((bool)markerList.Visible);
                recorder.Record((int)markerList.Width);
                recorder.Record((FormWindowState)markerList.WindowState);
                recorder.FinishRecording();
                #endregion
                #region Assertions
                Assert.IsNull((string)markerList.AccessibleDefaultActionDescription);
                Assert.IsFalse((bool)markerList.AllowDrop);
                Assert.AreEqual(global::System.Windows.Forms.AutoScaleMode.Font, (AutoScaleMode)markerList.AutoScaleMode);
                Assert.AreEqual(global::System.Windows.Forms.AutoValidate.EnablePreventFocusChange, (AutoValidate)markerList.AutoValidate);
                Assert.IsFalse((bool)markerList.CanFocus);
                Assert.AreEqual("ST Electronics Ltd", (string)markerList.CompanyName);
                Assert.IsFalse((bool)markerList.Created);
                Assert.IsTrue((bool)markerList.Enabled);
                Assert.IsTrue((bool)markerList.HasChildren);
                Assert.IsFalse((bool)markerList.InvokeRequired);
                Assert.IsFalse((bool)markerList.IsHandleCreated);
                Assert.IsFalse((bool)markerList.IsRestrictedWindow);
                Assert.IsFalse((bool)markerList.MaximizeBox);
                Assert.AreEqual(1.0, (double)markerList.Opacity, 1E-7);
                Assert.IsFalse((bool)markerList.RecreatingHandle);
                Assert.IsTrue((bool)markerList.ShowIcon);
                Assert.AreEqual(global::System.Windows.Forms.FormStartPosition.CenterScreen, (FormStartPosition)markerList.StartPosition);
                Assert.AreEqual("Data Marker Viewer", (string)markerList.Text);
                Assert.IsFalse((bool)markerList.TopMost);
                Assert.IsFalse((bool)markerList.Visible);
                #endregion
            }
        }

    }
}
